class TreeNode:

    def __init__(self, value):
        
        self.value = value
        self.left = None
        self.right = None


class BalancedBST:

    def __init__(self):
        self.root = None

    def contains(self, value):
        return self._search(self.root, value)

    def _search(self, node, value):

        if node is None:
            return False
        if value == node.value:
            return True
        elif value < node.value:
            return self._search(node.left, value)
        else:
            return self._search(node.right, value)

    def insert(self, value):

        if not self.contains(value):
            self.root = self._insert(self.root, value)

    def _insert(self, node, value):

        if node is None:
            return TreeNode(value)
        if value < node.value:
            node.left = self._insert(node.left, value)
        else:
            node.right = self._insert(node.right, value)
        return node

    def in_order_traversal(self):

        result = []
        self._in_order(self.root, result)
        return result

    def _in_order(self, node, result):

        if node is not None:
            self._in_order(node.left, result)
            result.append(node.value)
            self._in_order(node.right, result)


def remove_duplicates(array):
    tree = BalancedBST()

    # Step 1: Insert elements into the tree
    for element in array:
        tree.insert(element)

    # Step 2: Get the sorted elements without duplicates
    return tree.in_order_traversal()


# Example usage:
array = [4, 2, 7, 3, 2, 3, 8, 4, 1, 7]
result = remove_duplicates(array)
print("Array with duplicates:", array)
print("Array without duplicates:", result)
