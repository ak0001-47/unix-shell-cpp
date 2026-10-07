#include "parser.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>

std::string Parser::expand_variables(const std::string& input,bool allow_expansion)
{
    if (!allow_expansion)
    {
        return input;
    }

    std::string result;

    for (size_t i = 0; i < input.size(); ++i)
    {
        if (input[i] != '$')
        {
            result += input[i];
            continue;
        }

        if (i + 1 >= input.size())
        {
            result += '$';
            continue;
        }

        size_t start = i + 1;

        if (!(std::isalpha(
                static_cast<unsigned char>(input[start])
              ) ||
              input[start] == '_'))
        {
            result += '$';
            continue;
        }

        size_t end = start + 1;

        while (end < input.size())
        {
            char character = input[end];

            if (!(std::isalnum(
                    static_cast<unsigned char>(character)
                  ) ||
                  character == '_'))
            {
                break;
            }

            ++end;
        }

        std::string variable_name =
            input.substr(start, end - start);

        const char* value =
            std::getenv(variable_name.c_str());

        if (value != nullptr)
        {
            result += value;
        }

        i = end - 1;
    }

    return result;
}

std::vector<Token> Parser::tokenize(const std::string& input,bool& valid)
{
    std::vector<Token> tokens;

    std::string current;

    bool single_quotes = false;
    bool double_quotes = false;
    bool escaped = false;

    for (size_t i = 0; i < input.size(); ++i)
    {
        char character = input[i];

        if (escaped)
        {
            current += character;
            escaped = false;
            continue;
        }

        if (character == '\\' && !single_quotes)
        {
            escaped = true;
            continue;
        }

        if (character == '\'' && !double_quotes)
        {
            single_quotes = !single_quotes;
            continue;
        }

        if (character == '"' && !single_quotes)
        {
            double_quotes = !double_quotes;
            continue;
        }

       if (single_quotes)
      {
       current += character;
       continue;
    }

     if (character == '$')
    {
    std::string variable;

    size_t j = i + 1;

    if (j < input.size() &&
        (std::isalpha(
             static_cast<unsigned char>(input[j])
         ) ||
         input[j] == '_'))
    {
        while (j < input.size())
        {
            char variable_character = input[j];

            if (!(std::isalnum(
                    static_cast<unsigned char>(variable_character)
                  ) ||
                  variable_character == '_'))
            {
                break;
            }

            variable += variable_character;
            ++j;
        }

        const char* value =
            std::getenv(variable.c_str());

        if (value != nullptr)
        {
            current += value;
        }

        i = j - 1;
        continue;
    }

    current += '$';
    continue;
  }

if (double_quotes)
{
    current += character;
    continue;
}

       if (character == ' ' || character == '\t')
      {
        if (!current.empty())
       {
        bool allow_expansion = !single_quotes;

        tokens.push_back({
            expand_variables(current, allow_expansion)
        });

        current.clear();
    }

    continue;
    }

      if (character == '&')
   {
      if (!current.empty())
       {
          tokens.push_back({current});
          current.clear();
       }

       tokens.push_back({"&", true});
       continue;
    }

        if (character == '|')
        {
            if (!current.empty())
            {
                tokens.push_back({current});
                current.clear();
            }

           tokens.push_back({"|", true});
            continue;
        }

        if (character == '>')
        {
            if (!current.empty())
            {
                tokens.push_back({current});
                current.clear();
            }

            if (i + 1 < input.size() && input[i + 1] == '>')
            {
                tokens.push_back({">>", true});
                ++i;
            }
            else
            {
                tokens.push_back({">", true});
            }

            continue;
        }

        if (character == '<')
        {
            if (!current.empty())
            {
                tokens.push_back({current});
                current.clear();
            }

            tokens.push_back({"<", true});
            continue;
        }

        current += character;
    }

    if (escaped)
    {
        valid = false;
        return {};
    }

    if (single_quotes || double_quotes)
    {
        valid = false;
        return {};
    }

    if (!current.empty())
    {
        tokens.push_back({current});
    }

    return tokens;
}

Command Parser::parse_command(const std::vector<Token>& tokens)
{
    Command command;

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const std::string& token = tokens[i].value;

        if (token == ">" && tokens[i].operator_token)
        {
            if (i + 1 < tokens.size())
            {
                command.output_file = tokens[++i].value;
                command.append_output = false;
            }

            continue;
        }

        if (token == ">>" && tokens[i].operator_token)
        {
            if (i + 1 < tokens.size())
            {
                command.output_file = tokens[++i].value;
                command.append_output = true;
            }

            continue;
        }

        if (token == "<" && tokens[i].operator_token)
        {
            if (i + 1 < tokens.size())
            {
                command.input_file = tokens[++i].value;
            }

            continue;
        }

        command.arguments.push_back(token);
    }

    if (!command.arguments.empty())
    {
        command.program = command.arguments[0];
    }

    return command;
}

Pipeline Parser::parse(const std::string& input)
{
    Pipeline pipeline;

    std::string command_line = input;

    bool valid = true;

    std::vector<Token> tokens = tokenize(command_line,valid);

    if (!valid)
   {

    std::cerr << "mysh: unmatched quote or escape character\n";
    return pipeline;
   }


    std::vector<Token> command_tokens;

    for (const auto& token : tokens)
    {
        if (token.value == "&" && token.operator_token)
       {
           pipeline.background = true;
           continue;
        }

        if (token.value == "|" && token.operator_token)
        {
           if (!command_tokens.empty())
          {
              pipeline.commands.push_back(parse_command(command_tokens));

              command_tokens.clear();
           }

               continue;
       }

        command_tokens.push_back(token);
    }

    if (!command_tokens.empty())
    {
        pipeline.commands.push_back(
            parse_command(command_tokens)
        );
    }

    return pipeline;
}