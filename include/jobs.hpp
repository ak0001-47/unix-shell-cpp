#ifndef MYSH_JOBS_HPP
#define MYSH_JOBS_HPP

#include <sys/types.h>

#include <string>
#include <vector>

enum class JobState
{
    Running,
    Stopped,
    Done
};

struct Job
{
    int id;
    pid_t pid;
    pid_t pgid;
    std::string command;
    JobState state;
};

class JobManager
{
public:
    int add_job(pid_t pid, const std::string& command);

    void remove_job(int id);

    Job* find_job(int id);

    void print_jobs() const;

private:
    std::vector<Job> jobs;
    int next_job_id = 1;
};

#endif