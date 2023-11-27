#include <iostream>
#include <chrono>
#include <cstdlib>
#include <pthread.h>
#include <vector>

struct ThreadData {
  const int *arr;
  int start;
  int end;
  long long result;
};

long long computeSum(const int *arr, int size) {
  long long sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += arr[i];
  }
  return sum;
}

void *computeSumThread(void *arg) {
  ThreadData *data = static_cast<ThreadData *>(arg);
  data->result = 0;
  for (int i = data->start; i < data->end; ++i) {
    data->result += data->arr[i];
  }
  return nullptr;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "arguments are not enought" << std::endl;
    exit(0);
  }

  int N = std::atoi(argv[1]);
  int M = std::atoi(argv[2]);

  int *arr = new int[N];
  for (int i = 0; i < N; ++i) {
    arr[i] = std::rand();
  }

  auto start_time = std::chrono::high_resolution_clock::now();

  std::vector<pthread_t> threads(M);
  std::vector<ThreadData> thread_data(M);
  int portion_size = N / M;

  for (int i = 0; i < M - 1; ++i) {
    thread_data[i] = {arr, i * portion_size, (i + 1) * portion_size, 0};
    pthread_create(&threads[i], nullptr, computeSumThread, &thread_data[i]);
  }

  thread_data[M - 1] = {arr, (M - 1) * portion_size, N, 0};
  pthread_create(&threads[M - 1], nullptr, computeSumThread,
                 &thread_data[M - 1]);

  for (pthread_t &thread : threads) {
    pthread_join(thread, nullptr);
  }

  long long sum_with_threads = 0;
  for (const ThreadData &data : thread_data) {
    sum_with_threads += data.result;
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto time_with_threads = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();

  std::cout << "Time spent with " << M << " threads: " << time_with_threads << std::endl;

  delete[] arr;

  return 0;
}