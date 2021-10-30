/**
 * 红黑树特点:
 * 
 * 1、红链接均为左链接
 * 
 * 2、没有一个节点同时和两个红链接相连
 * 
 * 3、该树是完美黑色平衡的，即任意空链接到根节点的路径上的黑色链接数量相同
 * 
 * 满足这样定义的红黑树和相应的2-3树是一一对应的
 */
public class RedBlackBST<Key extends Comparable<Key>, Value> {
    // 颜色表示
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    // 根节点
    private Node root = null;

    /**
     * 节点颜色说明：
     * 
     * 节点的颜色代表的是指向该节点的链接的颜色，RED=true,BLACK=false
     * 
     * N是节点的数量，需要实现select(int k)方法(选择键值第k大的节点时)，可以用N进行递归实现
     */
    class Node {
        Key key;
        Value val;
        Node left, right;
        int N;
        boolean color;

        public Node(Key key, Value val, int n, boolean color) {
            this.key = key;
            this.val = val;
            N = n;
            this.color = color;
        }
    }

    private boolean isRed(Node x) {
        if (x == null)
            return false;
        return x.color;
    }

    public int size() {
        return size(root);
    }

    private int size(Node x) {
        if (x == null) {
            return 0;
        }
        return x.N;
    }

    Node rotateLeft(Node h) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = 1 + size(h.left) + size(h.right);
        return x;
    }

    Node rotateRight(Node h) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = 1 + size(h.left) + size(h.right);
        return x;
    }

    void flipColors(Node h) {
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    public void put(Key key, Value val) {
        root = put(root, key, val);
        root.color = BLACK;
    }

    private Node put(Node h, Key key, Value val) {
        if (h == null)
            return new Node(key, val, 1, RED);
        int cmp = key.compareTo(h.key);
        if (cmp < 0)
            h.left = put(h.left, key, val);
        else if (cmp > 0)
            h.right = put(h.right, key, val);
        else
            h.val = val;
        if (isRed(h.right) && !isRed(h.left))
            h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left))
            h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right))
            flipColors(h);
        h.N = 1 + size(h.left) + size(h.right);
        return h;
    }

    public Value get(Key key) {
        return get(root, key);
    }

    private Value get(Node x, Key key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            return get(x.left, key);
        else if (cmp > 0)
            return get(x.right, key);
        else
            return x.val;
    }

    public void pre_order() {
        pre_order(root);
    }

    private void pre_order(Node x) {
        if (x == null)
            return;
        System.out.print(x.val + "  ");
        pre_order(x.left);
        pre_order(x.right);
    }

    public void mid_order() {
        mid_order(root);
    }

    private void mid_order(Node x) {
        if (x == null)
            return;
        mid_order(x.left);
        System.out.print(x.val+"  ");
        mid_order(x.right);
    }

    public void post_order() {
        post_order(root);
    }

    private void post_order(Node x) {
        if (x == null)
            return;
        post_order(x.left);
        post_order(x.right);
        System.out.print(x.val+"  ");
    }
}