from typing import List
from common import format_test
from math import floor


class Solution:
    # 167. Two Sum II - Input array is sorted
    #  64 ms, faster than 54.07%
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        i, j = 0, len(numbers) - 1
        while i < j:
            twos = numbers[i] + numbers[j]
            if twos == target:
                return [i + 1, j + 1]
            elif twos > target:
                j = j - 1
            else:
                i = i + 1

    # 64 ms, faster than 54.07%
    def twoSumDC(self, numbers: List[int], target: int) -> List[int]:
        dc = {}
        for i, val in enumerate(numbers):
            if target - val in dc:
                return [dc[target - val], i + 1]
            dc[val] = i + 1

    #  116 ms, faster than 6.95%
    def twoSumBS(self, numbers: List[int], target: int) -> List[int]:
        l = len(numbers)
        mid = floor(l / 2)
        rightest = l - 1
        if numbers[0] > 0:
            rht = self.divide(numbers, target, 0, l - 1)
            if numbers[rht] != target:
                rightest = rht
        for i in range(mid + 1):
            left = i
            tar = target - numbers[left]
            if tar > numbers[rightest]:
                continue
            elif tar == numbers[rightest]:
                return [left + 1, rightest + 1]
            else:
                right = self.divide(numbers, tar, i + 1, rightest)
                if numbers[right] == tar:
                    return [left + 1, right + 1]

    def divide(self, numbers: List[int], target: int, start: int, end: int) -> List[int]:
        if start >= end:
            return start
        mid = start + floor((end - start + 1) / 2)
        if target == numbers[mid]:
            return mid
        elif target < numbers[mid]:
            return self.divide(numbers, target, start, mid - 1)
        else:
            return self.divide(numbers, target, mid + 1, end)

    def generate_input(self):
        return [[[-3, 3, 4, 90], 0]] + \
               [[[12, 13, 23, 28, 43, 44, 59, 60, 61, 68, 70, 86, 88, 92, 124, 125, 136, 168, 173, 173, 180, 199, 212,
                  221, 227, 230, 277, 282, 306, 314, 316, 321, 325, 328, 336, 337, 363, 365, 368, 370, 370, 371, 375,
                  384, 387, 394, 400, 404, 414, 422, 422, 427, 430, 435, 457, 493, 506, 527, 531, 538, 541, 546, 568,
                  583, 585, 587, 650, 652, 677, 691, 730, 737, 740, 751, 755, 764, 778, 783, 785, 789, 794, 803, 809,
                  815, 847,
                  858, 863, 863, 874, 887, 896, 916, 920, 926, 927, 930, 933, 957, 981, 997], 542]] + \
               [[[2, 7, 11, 15], 9]] + \
               [[[2, 3, 4], 6]] + \
               [[[-1, 0], -1]] + \
               [[[3, 24, 50, 79, 88, 150, 345], 200]]


if __name__ == "__main__":
    solu = Solution()
    format_test(solu.twoSum, solu.generate_input)
