# C_Processes_MessageQueues

![C Processes](https://img.shields.io/badge/C%20Processes-MessageQueues-brightgreen)

Welcome to the **C_Processes_MessageQueues** repository! These exercises were completed as part of the Operating Systems course during my Bachelor's Degree in Computer Science and Engineering at the University of Catania. This repository showcases various projects and exercises focused on processes and message queues in C programming.

## Table of Contents

- [Introduction](#introduction)
- [Topics Covered](#topics-covered)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)
- [Links](#links)

## Introduction

In this repository, you will find a collection of exercises that delve into key concepts of operating systems, specifically focusing on concurrent programming, data structures, and debugging techniques. Each exercise demonstrates how to implement and manage processes and message queues effectively using the C programming language.

## Topics Covered

This repository covers a range of topics essential for understanding operating systems and concurrent programming:

- **Algorithms**: Learn about various algorithms that optimize process management and message handling.
- **C**: The primary programming language used for all exercises.
- **Concurrent Programming**: Explore how multiple processes interact and communicate.
- **Data Structures**: Understand how to use data structures to manage processes and messages.
- **Debugging**: Learn techniques to debug concurrent applications.
- **English Language**: All documentation is in English to cater to a wider audience.
- **Git & GitHub**: Familiarize yourself with version control and collaboration.
- **Imperative Programming**: Gain insights into imperative programming concepts.
- **Markdown**: Documentation is formatted in Markdown for clarity and ease of use.
- **Project Management**: Understand how to manage and organize projects effectively.

## Installation

To get started with the exercises in this repository, follow these steps:

1. **Clone the Repository**: Use the following command to clone the repository to your local machine:
   ```bash
   git clone https://github.com/Raadkid/C_Processes_MessageQueues.git
   ```

2. **Navigate to the Directory**: Change into the project directory:
   ```bash
   cd C_Processes_MessageQueues
   ```

3. **Compile the Code**: Use a C compiler like `gcc` to compile the exercises. For example:
   ```bash
   gcc -o example example.c
   ```

4. **Run the Executable**: Execute the compiled program:
   ```bash
   ./example
   ```

## Usage

Each exercise is designed to be self-contained. To run a specific exercise, navigate to its folder and follow the compilation and execution steps outlined above. You can find the compiled binaries in their respective directories.

## Examples

Here are some examples of the exercises included in this repository:

### Example 1: Basic Message Queue Implementation

This exercise demonstrates how to create a simple message queue using the POSIX message queue API. It includes functions to send and receive messages between processes.

#### Code Snippet
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/example_queue"
#define MAX_SIZE 1024

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, NULL);
    mq_receive(mq, buffer, MAX_SIZE, NULL);
    printf("Received: %s\n", buffer);
    mq_close(mq);
    return 0;
}
```

### Example 2: Process Synchronization

In this exercise, you will learn how to synchronize multiple processes using semaphores. This example demonstrates how to prevent race conditions.

#### Code Snippet
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void* thread_function(void* arg) {
    sem_wait(&semaphore);
    // Critical section
    printf("Thread %d is in the critical section.\n", *((int*)arg));
    sem_post(&semaphore);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_args[5];

    sem_init(&semaphore, 0, 1);
    for (int i = 0; i < 5; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore);
    return 0;
}
```

## Contributing

Contributions are welcome! If you would like to add new exercises or improve existing ones, please follow these steps:

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/YourFeature
   ```
3. Make your changes and commit them:
   ```bash
   git commit -m "Add your message here"
   ```
4. Push to your branch:
   ```bash
   git push origin feature/YourFeature
   ```
5. Create a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Links

For downloadable files and to check for the latest updates, visit the [Releases](https://github.com/Raadkid/C_Processes_MessageQueues/releases) section. You can find the compiled binaries and other important files there.

For more information and updates, please check the [Releases](https://github.com/Raadkid/C_Processes_MessageQueues/releases) section.

Feel free to explore the exercises and improve your understanding of operating systems and concurrent programming!