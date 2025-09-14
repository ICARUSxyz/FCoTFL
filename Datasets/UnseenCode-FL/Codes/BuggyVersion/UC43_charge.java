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

        //残高の表示: ラベル
        JPanel panel0 = new JPanel();
        panel0.setLayout(new BoxLayout(panel0, BoxLayout.Y_AXIS));  // 縦方向に配置
        frame.add(panel0, BorderLayout.CENTER);
        JLabel balanceLabel = new JLabel("<html><font color='red'>balance : " + balance + " yen</font>");
        panel0.add(balanceLabel);

        panel0.add(Box.createVerticalStrut(20)); //ラベル間に空白を追加

        //チャージ
        min = "1000";
        max = Integer.toString(500000 - Integer.parseInt(balance));
        if(490000 < Integer.parseInt(balance)){
            min = "-";
            max = "-";
        }
        
        JLabel label1 = new JLabel("Plese enter the amount to charge.");
        panel0.add(label1);
        JLabel label2 = new JLabel("<html><font color='blue'>min:" +min+ "yen</font></html>");
        panel0.add(label2);
        JLabel label3 = new JLabel("<html><font color='blue'>max:" +max+ " yen</font></html>");
        panel0.add(label3);

        panel0.add(Box.createVerticalStrut(20)); //ラベル間に空白を追加
        
        JLabel chargeLimit = new JLabel("");
        panel0.add(chargeLimit);
        if(490000 < Integer.parseInt(balance)){
            chargeLimit.setText("The maximum charge amount has been reached.You can't charge.");
        }
    }

    public static void main(String[] args) {
        new charge();
    }
}