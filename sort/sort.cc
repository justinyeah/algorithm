#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

void swap(std::vector<int> &nums, int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

int generate_random(int range_l, int range_r){
    std::random_device gt;
    std::mt19937 random_gt(gt());
    std::uniform_int_distribution<int> distribution(1, 100);
    int rand_number = distribution(random_gt);
    return rand_number;
}

void select_sort(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    for (int i = 0; i < nums.size(); i++) {
       int min_index = i;
       for (int j = i + 1; j < nums.size(); j++) {
           min_index = nums[j] < nums[min_index] ? j : min_index;
       }
       swap(nums, min_index, i);
    }
}

void bubble_sort(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size() - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                swap(nums, j, j + 1);
            }
        }
    }
}

void insert_sort(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j > 0 && nums[j - 1] > nums[j] && j < nums.size(); j--) {
            swap(nums, j, j - 1);
        }
    }
}

void merge_sort(std::vector<int>& nums, int i, int j) {
    if (i == j) return;
    int mid = (i + j) / 2;
    merge_sort(nums, i, mid);
    merge_sort(nums, mid + 1, j);
    int k = i, m = mid + 1;
    std::vector<int> tmp;
    tmp.reserve(j - i + 1);
    while (k <= mid && m <= j) {
        if (nums[k] <= nums[m]) {
            tmp.push_back(nums[k++]);
        }
        else {
            tmp.push_back(nums[m++]);
        }
    }
    while (k <= mid) {
        tmp.push_back(nums[k++]);
    }
    while (m <= j) {
        tmp.push_back(nums[m++]);
    }
    for (int s = 0; s < tmp.size(); s++) {
        nums[i + s] = tmp[s];
    }
}

void merge_sort(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    merge_sort(nums, 0, nums.size() - 1);
}

std::vector<int> partition(std::vector<int>& nums, int i, int j) {
    int l = i - 1, r = j + 1;
    int partition_num = nums[j];
    int index = i;
    while (index < r) {
        if (nums[index] < partition_num) {
            swap(nums, l + 1, index);
            index++;
            l++;
        }
        else if (nums[index] == partition_num) {
            index++;
        }
        else {
            swap(nums, index, r - 1);
            r--;
        }
    }
    return {l, r};
}

void quick_sort(std::vector<int>& nums, int i, int j) {
    if (i >= j) return;
    std::vector<int> partition_res = partition(nums, i, j);
    quick_sort(nums, i, partition_res[0]);
    quick_sort(nums, partition_res[1], j);
}

void quick_sort(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    quick_sort(nums, 0, nums.size() - 1);
}


void heap_insert(std::vector<int>& nums, int i) {
    while (nums[i] > nums[(i - 1) / 2]) {
        swap(nums, (i - 1) / 2, i);
        i = (i - 1) / 2;
    }
}

void heapify(std::vector<int>& nums, int i, int size) {
    int lc = 2 * i + 1;
    while (lc < size) {
        int best_c = (lc + 1 < size && nums[lc + 1] > nums[lc]) ? lc + 1 : lc;
        best_c = nums[best_c] > nums[i] ? best_c : i;
        if (best_c == i) {
            break;
        }
        swap(nums, i, best_c);
        i = best_c;
        lc = 2 * i + 1;
    }
}

void heap_sort(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    for (int i = 0; i < nums.size(); i++) {
        heap_insert(nums, i);
    }
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        swap(nums, 0, n - i - 1);
        heapify(nums, 0, n - i - 1);
    }
}

void verify_sort(int n = 1) {
    for (int i = 0; i < n; i++) {
        int length = generate_random(2, 20);
        std::vector<int> nums;
        nums.reserve(length);
        for (int i = 0; i < length; i++) {
            nums.push_back(generate_random(1, 50));
        }
        std::vector<int> std_nums = nums, select_sort_nums = nums,
                         bubble_nums = nums, insert_nums = nums,
                         merge_nums = nums, quick_nums = nums,
                         heap_nums = nums;
        select_sort(select_sort_nums);
        bubble_sort(bubble_nums);
        insert_sort(insert_nums);
        merge_sort(merge_nums);
        quick_sort(quick_nums);
        heap_sort(heap_nums);
        std::sort(std_nums.begin(), std_nums.end());
        for (int i = 0; i < length; i++) {
            if (std_nums[i] != select_sort_nums[i] || std_nums[i] != bubble_nums[i] ||
                insert_nums[i] != std_nums[i] || std_nums[i] != merge_nums[i] ||
                std_nums[i] != quick_nums[i] || heap_nums[i] != std_nums[i]) {
                for (int j = 0; j < nums.size(); ++j) {
                    std::cout << nums[j] << " ";
                }
                std::cout << std::endl;
                std::cout << "failed" << std::endl;
                return;
            }
        }
    }
    std::cout << "succucess" << std::endl;
}
void verify_partition(int n = 1) {
    for (int i = 0; i < n; i++) {
        int length = generate_random(2, 100);
        std::vector<int> nums;
        nums.reserve(length);
        for (int i = 0; i < length; i++) {
            nums.push_back(generate_random(1, 300));
        }
        std::cout << nums[0] << " " << nums[1] << std::endl;
        int partition_num = nums.back();
        std::vector<int> res = partition(nums, 0, nums.size() - 1);
        for (int i = 0; i <= res[0]; i++) {
            if (nums[i] >= partition_num) {
                std::cout << "failed" << std::endl;
                return;
            }
        }
        for (int i = res[0] + 1; i < res[1]; i++) {
            if (nums[i] != partition_num) {
                std::cout << "failed" << std::endl;
                return;
            }
        }
        for (int i = res[1]; i < nums.size(); i++) {
            if (nums[i] <= partition_num) {
                std::cout << "failed" << std::endl;
                return;
            }
        }
    }
    std::cout << "succucess" << std::endl;
}


int main() {
    // verify_partition(100);
    verify_sort(1000000);
    return 0;
}
