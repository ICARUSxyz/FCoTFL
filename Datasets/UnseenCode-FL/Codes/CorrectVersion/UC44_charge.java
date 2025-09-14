import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import javax.swing.*;

public class charge {

    private String balance = "";
    private String min;
    private String max;

    charge() {
        // JFrameのインスタンスを作成
        JFrame frame = new JFrame("charge");

        // ウィンドウのサイズを指定
        frame.setSize(new Dimension(500, 800));

        // デフォルトの閉じる動作を設定
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //残高をbalance.csvファイルから読み込む
        file f = new file();
        try {
            balance = f.readFile("balance.csv");
            //System.out.println(balance);
        } catch (IOException e) {
            e.printStackTrace();
        }

        //チャージ履歴の閲覧
        JButton btn1 = new JButton("View charging history.");
        panel0.add(btn1);

        panel0.add(Box.createVerticalStrut(500)); //ラベル間に空白を追加

        //ページ移動
        JPanel panel = new JPanel(new BorderLayout());
        frame.add(panel, BorderLayout.SOUTH);
        JPanel panel1 = new JPanel();
        panel.add(panel1, BorderLayout.SOUTH);
        panel1.setLayout(new BoxLayout(panel1, BoxLayout.X_AXIS));

       JButton subPanel1 = new JButton();
        subPanel1.add(new JLabel("wallet"));
        Dimension buttonSize = new Dimension(106, 106);
        subPanel1.setPreferredSize(buttonSize);
        subPanel1.setMinimumSize(buttonSize);
        subPanel1.setMaximumSize(buttonSize);
        subPanel1.setSize(buttonSize);
        subPanel1.setBackground(Color.WHITE);
        panel1.add(subPanel1);

        JButton subPanel2 = new JButton();
        subPanel2.add(new JLabel("settlement"));
        subPanel2.setPreferredSize(buttonSize);
        subPanel2.setMinimumSize(buttonSize);
        subPanel2.setMaximumSize(buttonSize);
        subPanel2.setSize(buttonSize);
        subPanel2.setBackground(Color.WHITE);
        panel1.add(subPanel2);

        JButton subPanel3 = new JButton();
        subPanel3.add(new JLabel("charge"));
        subPanel3.setPreferredSize(buttonSize);
        subPanel3.setMinimumSize(buttonSize);
        subPanel3.setMaximumSize(buttonSize);
        subPanel3.setSize(buttonSize);
        subPanel3.setBackground(Color.CYAN); // 背景色を青に設定
        subPanel3.setForeground(Color.WHITE); // テキストの色を白に設定
        panel1.add(subPanel3);

        JButton subPanel4 = new JButton();
        subPanel4.add(new JLabel("coupon"));
        subPanel4.setPreferredSize(buttonSize);
        subPanel4.setMinimumSize(buttonSize);
        subPanel4.setMaximumSize(buttonSize);
        subPanel4.setSize(buttonSize);
        subPanel4.setBackground(Color.WHITE);
        panel1.add(subPanel4);

        // ウィンドウを表示
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new charge();
    }
}