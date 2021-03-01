import typing.List

from collections import deque


# Definition for a binary tree node.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
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
