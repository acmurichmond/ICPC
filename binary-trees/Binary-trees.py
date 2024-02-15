# Binary Tree in Python
#General Implementation

#Reviewed by Caitlin, Andrew. 
#Files provide example of post, pre, in order traversals but wouldn't be directly used. Also, should be present in C++ as well as Python.
#(Seems correct, needs improvement)

class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.val = key

    # Traverse preorder
    def traversePreOrder(self):
        print(self.val, end=' ')
        if self.left:
            self.left.traversePreOrder()
        if self.right:
            self.right.traversePreOrder()

    # Traverse inorder
    def traverseInOrder(self):
        if self.left:
            self.left.traverseInOrder()
        print(self.val, end=' ')
        if self.right:
            self.right.traverseInOrder()

    # Traverse postorder
    def traversePostOrder(self):
        if self.left:
            self.left.traversePostOrder()
        if self.right:
            self.right.traversePostOrder()
        print(self.val, end=' ')
        
    # Checking full binary tree
    def isFullTree(self,root):

        # Tree empty case
        if root is None:
            return True

        # Checking whether child is present
        if root.left is None and root.right is None:
            return True

        if root.left is not None and root.right is not None:
            return (self.isFullTree(root.left) and self.isFullTree(root.right))

        return False
    
    # Calculate the depth
    def calculateDepth(self,node):
        d = 0
        while (node is not None):
            d += 1
            node = node.left
        return d
    
    # Check if the tree is perfect binary tree
    def is_perfect(self,root, d, level=0):

        # Check if the tree is empty
        if (root is None):
            return True

        # Check the presence of trees
        if (root.left is None and root.right is None):
            return (d == level + 1)

        if (root.left is None or root.right is None):
            return False

        return (self.is_perfect(root.left, d, level + 1) and
                self.is_perfect(root.right, d, level + 1))
        
    # Count the number of nodes
    def count_nodes(self,root):
        if root is None:
            return 0
        return (1 + self.count_nodes(root.left) + self.count_nodes(root.right))
    
    # Check if the tree is complete binary tree
    def is_complete(self,root, index, numberNodes):

        # Check if the tree is empty
        if root is None:
            return True

        if index >= numberNodes:
            return False

        return (self.is_complete(root.left, 2 * index + 1, numberNodes)
                and self.is_complete(root.right, 2 * index + 2, numberNodes))
        
    

#Drive and testing code

root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(4)

print("Pre order Traversal: ", end="")
root.traversePreOrder()
print("\nIn order Traversal: ", end="")
root.traverseInOrder()
print("\nPost order Traversal: ", end="")
root.traversePostOrder()
print("\n")
#check if tree is full
print(root.isFullTree(root))
#check if tree is perfect
print(root.is_perfect(root, root.calculateDepth(root)))
#check if binary tree is complete
print(root.is_complete(root, 0, root.count_nodes(root)))

