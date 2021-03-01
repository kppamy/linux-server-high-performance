import typing.List

from collections import deque


# Definition for a binary tree node.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    # 665. Non-decreasing Array
    # 180 ms, faster than 83.86%
    # 15.4 MB, less than 24.34%
    def checkPossibility(self, nums: List[int]) -> bool:
        sz = len(nums)
        modified = False
        for idx, val in enumerate(nums):
            if idx < sz - 1 and nums[idx] > nums[idx + 1]:
                if modified:
                    return False
                if idx > 0 and nums[idx - 1] <= nums[idx + 1]:
                    nums[idx] = nums[idx - 1]
                elif idx == 0:
                    nums[idx] = nums[idx + 1] - 1
                else:
                    nums[idx + 1] = nums[idx]
                modified = True
        return True

    # 1379. Find a Corresponding Node of a Binary Tree in a Clone of That Tree
    # : 628 ms, faster than 60.07% o
    #  24.1 MB, less than 56.71%
    def getTargetCopy(self, original: TreeNode, cloned: TreeNode, target: TreeNode) -> TreeNode:
        s1 = deque()
        s2 = deque()
        s1.append(original)
        s2.append(cloned)
        while len(s1) > 0:
            tp1 = s1.pop()
            tp2 = s2.pop()
            if tp1.val == target.val:
                return tp2
            if tp1.left is not None:
                s1.append(tp1.left)
                s2.append(tp2.left)
            if tp1.right is not None:
                s1.append(tp1.right)
                s2.append(tp2.right)

    # 897. Increasing Order Search Tree
    #  32 ms, faster than 66.58%
    # 14.3 MB, less than 47.06%
    def increasingBST(self, root: TreeNode) -> TreeNode:
        stack = deque()
        dummy = TreeNode()
        head = dummy
        if root is not None:
            stack.append(root)
        while len(stack) > 0:
            tp = stack.pop()
            if tp.left is None and tp.right is None:
                dummy.right = tp
                dummy = tp
            elif tp.left is not None:
                stack.append(tp)
                stack.append(tp.left)
                tp.left = None
            elif tp.right is not None:
                dummy.right = tp
                dummy = tp
                stack.append(tp.right)
                tp.right = None
        return head.right

    # 1588. Sum of All Odd Length Subarrays
    def sumOddLengthSubarrays(self, arr: List[int]) -> int:
        size = len(arr)
        ans = 0
        for win in range(1, size + 1, 2):
            for start in range(size - win + 1):
                ans = ans + sum(arr[start:start + win])
        return ans
