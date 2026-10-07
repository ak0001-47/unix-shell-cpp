#include "jobs.hpp"

#include <iostream>

int JobManager::add_job(
    pid_t pid,
    const std::string& command
)
{
    Job job;

    job.id = next_job_id++;
    job.pid = pid;
    job.command = command;
    job.state = JobState::Running;

    jobs.push_back(job);

    return job.id;
}

void JobManager::remove_job(int id)
{
    for (auto it = jobs.begin(); it != jobs.end(); ++it)
    {
        if (it->id == id)
        {
            jobs.erase(it);
            return;
        }
    }
}

Job* JobManager::find_job(int id)
{
    for (auto& job : jobs)
    {
        if (job.id == id)
        {
            return &job;
        }
    }

    return nullptr;
}

void JobManager::print_jobs() const
{
    for (const auto& job : jobs)
    {
        std::cout << "[" << job.id << "] ";

        if (job.state == JobState::Running)
        {
            std::cout << "Running";
        }
        else if (job.state == JobState::Stopped)
        {
            std::cout << "Stopped";
        }
        else
        {
            std::cout << "Done";
        }

        std::cout << "    " << job.command << '\n';
    }
}