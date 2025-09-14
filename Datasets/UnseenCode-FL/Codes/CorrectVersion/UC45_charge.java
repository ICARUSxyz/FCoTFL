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

        charge.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    // テキストフィールドから取得した文字列を整数に変換
                    String inputText = chargeText.getText().trim();
                    
                    if (inputText.isEmpty()) {
                        throw new NumberFormatException("入力が空です。");
                    }

                    int charge = Integer.parseInt(inputText);

                    if(Integer.parseInt(min) < charge && charge <= Integer.parseInt(max)) {
                        System.out.println("チャージしました。");
                        
                        // 現在の残高にチャージ金額を加算
                        int chargeAndBalance = Integer.parseInt(balance) + charge;
                        f.writeFile(String.valueOf(chargeAndBalance), "balance.csv");
                        
                        JOptionPane.showMessageDialog(frame, "Charging completed.");
                        
                        // 残高表示の更新
                        balanceLabel.setText("<html><font color='red'>balance : " + chargeAndBalance + " yen</font> </html>");

                        f.writeFile2(inputText, "charge_data.csv", " yen charged.");

                        //チャージ可能額の表示
                        min = "1000";
                        max = Integer.toString(500000 - chargeAndBalance);
                        if(499000 < chargeAndBalance){
                            min = "-";
                            max = "-";
                        }

                        label2.setText("<html><font color='blue'>min:" +min+ "yen</font></html>");
                        label3.setText("<html><font color='blue'>max:" +max+ " yen</font></html>");
                        
                                        
                        //チャージテキストボックスの初期化
                        chargeText.setText("");
            

                    } else {
                        JOptionPane.showMessageDialog(frame, "Please enter the correct amount.");
                    }

                } catch (NumberFormatException ex) {
                    System.out.println("入力が無効です: " + ex.getMessage());
                    JOptionPane.showMessageDialog(frame, "Error.");
                }
            }
        });

        //ページ移動
        subPanel1.addActionListener(new ActionListener(){ 
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.setVisible(false);
                new wallet();
            }
        });

        subPanel2.addActionListener(new ActionListener(){ 
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.setVisible(false);
                new settlement();
            }
        });

        subPanel4.addActionListener(new ActionListener(){ 
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.setVisible(false);
                new coupon();
            }
        });
    }

    public static void main(String[] args) {
        new charge();
    }
}