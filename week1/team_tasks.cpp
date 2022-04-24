#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

TasksInfo operator+ (TasksInfo& lhs, TasksInfo& rhs) {
    TasksInfo result;
    
    result[TaskStatus::NEW] = lhs[TaskStatus::NEW] + rhs[TaskStatus::NEW];
    result[TaskStatus::IN_PROGRESS] = lhs[TaskStatus::IN_PROGRESS] + rhs[TaskStatus::IN_PROGRESS];
    result[TaskStatus::TESTING] = lhs[TaskStatus::TESTING] + rhs[TaskStatus::TESTING];
    result[TaskStatus::DONE] = lhs[TaskStatus::DONE] + rhs[TaskStatus::DONE];

    return result;
}

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const;
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person);

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count);

private:
    map<string, TasksInfo> person_to_tasks;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
    return person_to_tasks.at(person);
}

// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
void TeamTasks::AddNewTask(const string& person) {
    ++person_to_tasks[person][TaskStatus::NEW];
}

void RemoveZeros(TasksInfo& info_for_proccesing) {
    vector<TaskStatus> statuses_to_remove;
    for (const auto& task_item : info_for_proccesing) {
        if (task_item.second == 0) {
            statuses_to_remove.push_back(task_item.first);
        }
    }
    for (const TaskStatus status : statuses_to_remove) {
        info_for_proccesing.erase(status);
    }
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
        const string& person, int task_count) {

    TasksInfo updated_tasks, untouched_tasks;
    untouched_tasks = person_to_tasks[person];

    for (auto& task : untouched_tasks) {
        if (task.first == TaskStatus::NEW) {
            if (task.second > 0) {
                while (task.second > 0 && task_count > 0) {
                    --untouched_tasks[TaskStatus::NEW];
                    ++updated_tasks[TaskStatus::IN_PROGRESS];
                    --task_count;
                }
            }
        }
        if (task.first == TaskStatus::IN_PROGRESS) {
            if (task.second > 0) {
                while (task.second > 0 && task_count > 0) {
                    --untouched_tasks[TaskStatus::IN_PROGRESS];
                    ++updated_tasks[TaskStatus::TESTING];
                    --task_count;
                }
            }
        }
        if (task.first == TaskStatus::TESTING) {
            if (task.second > 0) {
                while (task.second > 0 && task_count > 0) {
                    --untouched_tasks[TaskStatus::TESTING];
                    ++updated_tasks[TaskStatus::DONE];
                    --task_count;
                }
            }
        }
    }

    person_to_tasks[person] = untouched_tasks + updated_tasks;
    RemoveZeros(untouched_tasks);
    RemoveZeros(updated_tasks);
    RemoveZeros(person_to_tasks[person]);
    untouched_tasks.erase(TaskStatus::DONE);
    return tie(updated_tasks, untouched_tasks);
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }

    TasksInfo updated_tasks, untouched_tasks;
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 5);
    cout << "Updated Alice's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Alice's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 5);
    cout << "Updated Alice's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Alice's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 1);
    cout << "Updated Alice's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Alice's tasks: ";
    PrintTasksInfo(untouched_tasks);

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 2);
    cout << "Updated Alice's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Alice's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tasks.GetPersonTasksInfo("Alice");

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 4);
    cout << "Updated Alice's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Alice's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tasks.GetPersonTasksInfo("Alice");
    
    return 0;
}
