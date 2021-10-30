public class Main {
    public static void main(String[] args) {
        RedBlackBST<Integer, Integer> tree = new RedBlackBST<>();
        for (int i = 0; i < 10; i++) {
            tree.put(i, i);
        }
        tree.pre_order();
        System.out.println();
        tree.mid_order();
        System.out.println();
        tree.post_order();
    }
}

/**
 * 输出结果：
 * 前序：3  1  0  2  7  5  4  6  9  8
 * 中序：0  1  2  3  4  5  6  7  8  9
 * 后序：0  2  1  4  6  5  8  9  7  3
 */