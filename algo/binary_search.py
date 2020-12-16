from typing import List
from common import format_test
from math import floor


class Solution:
    # 34. Find First and Last Position of Element in Sorted Array
    #  80 ms, faster than 83.36%
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        l = len(nums)
        if l == 0:
            return [-1, -1]
        left = self.searchBorder(nums, target, 0, l - 1)
        if left == -1:
            return [-1, -1]
        if left == l - 1 or nums[left + 1] > nums[left]:
            return [left, left]
        right = self.searchBorder(nums, target, 0, l - 1, True)
        return [left, right]

    def searchBorder(self, numbers: List[int], target: int, start: int, end: int, rightB=False) -> List[int]:
        if start >= end:
            if numbers[start] == target:
                return start
            else:
                return -1
        if rightB:
            mid = start + floor((end - start + 1) / 2)
            if target >= numbers[mid]:
                left = mid
                right = end
            else:
                left = start
                right = mid - 1
        else:
            mid = start + floor((end - start) / 2)
            if target <= numbers[mid]:
                left = start
                right = mid
            else:
                left = mid + 1
                right = end
        return self.searchBorder(numbers, target, left, right, rightB)

    def generate_range(self):
        cases = []

        nums = [5, 7, 7, 8, 8, 10]
        target = 6
        cases = cases + [[nums, target]]

        nums = [5, 7, 7, 8, 8, 10]
        target = 8
        cases = cases + [[nums, target]]

        nums = []
        target = 0
        cases = cases + [[nums, target]]

        return cases

    # 744. Find Smallest Letter Greater Than Target
    # 112 ms, faster than 34.94%
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        if target == 'z':
            return letters[0]
        idx = self.searchLetter(letters, target, 0, len(letters) - 1)
        if letters[idx] <= target:
            return letters[0]
        return letters[idx]

    def searchLetter(self, letters: List[str], target: str, start: int, end: int):
        if start >= end:
            return end
        if letters[start] > target:
            return start
        mid = start + floor((end - start + 1) / 2)
        if letters[mid] > target and mid >= 1 and letters[mid - 1] <= target:
            return mid
        elif letters[mid] <= target:
            return self.searchLetter(letters, target, mid + 1, end)
        elif letters[mid] > target:
            return self.searchLetter(letters, target, start, mid)

    def genrate_letter(self):
        cases = []

        letters = ['a', 'b']
        target = "z"
        cases = cases + [[letters, target]]

        letters = ["c", "f", "j"]
        target = "a"
        cases = cases + [[letters, target]]

        letters = ["c", "f", "j"]
        target = "c"
        cases = cases + [[letters, target]]

        letters = ["c", "f", "j"]
        target = "d"
        cases = cases + [[letters, target]]

        letters = ["c", "f", "j"]
        target = "g"
        cases = cases + [[letters, target]]

        letters = ["c", "f", "j"]
        target = "j"
        cases = cases + [[letters, target]]

        letters = ["c", "f", "j"]
        target = "k"
        cases = cases + [[letters, target]]

        return cases

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
    # format_test(solu.twoSum, solu.generate_input)
    # format_test(solu.nextGreatestLetter, solu.genrate_letter)
    format_test(solu.searchRange, solu.generate_range)
