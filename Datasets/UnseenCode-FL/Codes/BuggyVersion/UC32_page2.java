import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.time.LocalDateTime;

public class page2 extends JPanel {
    private JTextField amountTextField;
    private JRadioButton pointUseButton, pointNotUseButton;
    private ButtonGroup buttonGroup;
    private JButton paymentButton;
    private boolean usePoint;
    public static final Integer[] COUPON_RATES = {0, 10, 20, 30, 40, 50};
    private JComboBox<Integer> couponComboBox;
    private JLabel discountedAmountLabel;

    public page2() {
        // レイアウトの設定
        setLayout(new FlowLayout()); // レイアウトをFlowLayoutに変更
        
        // 支払金額入力欄
        JLabel amountLabel = new JLabel("支払金額:");
        add(amountLabel);
        amountTextField = new JTextField(10); // 幅を指定
        add(amountTextField);
        add(new JLabel("円"));

    // 決済ボタン
        paymentButton = new JButton("決済");
        paymentButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // ポイント使用時の処理
                if (usePoint) {
                    int currentPoint = UserData.getPoint();
                    if (currentPoint > discountedAmount) {
                        // ポイントで全額支払う
                        UserData.setPoint(currentPoint - discountedAmount);
                        discountedAmount = 0;
                    } else {
                        // ポイントで支払えるだけ支払う
                        discountedAmount -= currentPoint;
                        UserData.setPoint(currentPoint);
                    }
                }

                // 残高の更新
                UserData.setBalance(UserData.getBalance() - discountedAmount);

                // ポイントの付与 (100円ごとに1ポイント)
                int earnedPoint = discountedAmount / 10;
                UserData.setPoint(UserData.getPoint() + earnedPoint);

                int usedPoint = usePoint ? Math.min(discountedAmount, UserData.getPoint()) : 0;
                // 決済履歴の保存
                LocalDateTime now = LocalDateTime.now();
                PaymentLog.save(discountedAmount, usedPoint, now);  

                // 決済完了メッセージを表示
                JOptionPane.showMessageDialog(null, "決済が完了しました。");

                // MainFrameのインスタンスを取得して、updatePages()メソッドを呼び出す
                MainFrame mainFrame = (MainFrame) SwingUtilities.getwindowAncestor(page2.this);
                mainFrame.updatePages();
                
                // 割引後の金額を表示
                discountedAmountLabel.setText("割引後金額: " + discountedAmount + "円");
            }
        });
        add(paymentButton);

        // 割引後の金額を表示するラベル
        discountedAmountLabel = new JLabel();
        add(discountedAmountLabel);
    }
}