#include <memory>
#include <vector>
#include <iostream>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

class BubbleSort : public Strategy {
public:
    void sort(std::vector<int>& data) override {
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

class QuickSort : public Strategy {
public:
    void sort(std::vector<int>& data) override {
        quickSort(data, 0, data.size() - 1);
    }

private:
    void quickSort(std::vector<int>& data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

    int partition(std::vector<int>& data, int low, int high) {
        int pivot = data[high];
        int i = (low - 1);
        for (int j = low; j < high; ++j) {
            if (data[j] < pivot) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return (i + 1);
    }
};

class MergeSort : public Strategy {
public:
    void sort(std::vector<int>& data) override {
        if (data.size() > 1) {
            mergeSort(data, 0, data.size() - 1);
        }
    }

private:
    void mergeSort(std::vector<int>& data, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(data, left, mid);
            mergeSort(data, mid + 1, right);
            merge(data, left, mid, right);
        }
    }

    void merge(std::vector<int>& data, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> leftArray(n1);
        std::vector<int> rightArray(n2);

        for (int i = 0; i < n1; ++i) {
            leftArray[i] = data[left + i];
        }
        for (int j = 0; j < n2; ++j) {
            rightArray[j] = data[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArray[i] <= rightArray[j]) {
                data[k] = leftArray[i];
                ++i;
            } else {
                data[k] = rightArray[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            data[k] = leftArray[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            data[k] = rightArray[j];
            ++j;
            ++k;
        }
    }
};


class Context {
public:
    void setStrategy(std::shared_ptr<Strategy> strategy) {
        this->strategy = strategy;
    }

    void executeStrategy(std::vector<int>& data) {
        if (strategy) {
            strategy->sort(data);
        }
    }

private:
    std::shared_ptr<Strategy> strategy;
};

int main() {
    std::vector<int> data = {34, 7, 23, 32, 5, 62};

    Context context;

    std::cout << "Original data: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Using BubbleSort
    context.setStrategy(std::make_shared<BubbleSort>());
    context.executeStrategy(data);

    std::cout << "BubbleSorted data: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Reset data
    data = {34, 7, 23, 32, 5, 62};

    // Using QuickSort
    context.setStrategy(std::make_shared<QuickSort>());
    context.executeStrategy(data);

    std::cout << "QuickSorted data: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Reset data
    data = {34, 7, 23, 32, 5, 62};

    // Using MergeSort
    context.setStrategy(std::make_shared<MergeSort>());
    context.executeStrategy(data);

    std::cout << "MergeSorted data: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
