
import typing.List

class Solution:
    # 1588. Sum of All Odd Length Subarrays
    def sumOddLengthSubarrays(self, arr: List[int]) -> int:
        size = len(arr)
        ans = 0
        for win in range(1,size + 1, 2):
            for start in range(size - win + 1):
                ans  = ans + sum(arr[start:start+win])
        return ans