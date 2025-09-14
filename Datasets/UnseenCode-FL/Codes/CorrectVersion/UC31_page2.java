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

        // ポイント使用ラジオボタン
        pointUseButton = new JRadioButton("ポイントを使用する");
        buttonGroup = new ButtonGroup();
        buttonGroup.add(pointUseButton);
        pointNotUseButton = new JRadioButton("使用しない");
        buttonGroup.add(pointNotUseButton);
        JPanel radioPanel = new JPanel();
        radioPanel.add(pointUseButton);
        radioPanel.add(pointNotUseButton);
        add(radioPanel);

        // クーポン選択
        JLabel couponLabel = new JLabel("クーポンを選ぶ");
        add(couponLabel);
        couponComboBox = new JComboBox<>(COUPON_RATES);
        couponComboBox.setSelectedIndex(0);
        add(couponComboBox);
        add(new JLabel("%"));

        // 決済ボタン
        paymentButton = new JButton("決済");
        paymentButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int paymentAmount = Integer.parseInt(amountTextField.getText());
                usePoint = pointUseButton.isSelected();

                // クーポン割引率を取得
                int couponRate = (int) couponComboBox.getSelectedItem();

                // 決済金額を計算 (クーポン割引を適用)
                int discountedAmount = paymentAmount - (paymentAmount * couponRate / 100);

                // 残高チェック (割引後の金額でチェック)
                if (discountedAmount > UserData.getBalance()) {  
                    JOptionPane.showMessageDialog(null, "残高が不足しています。");
                    return;
                }
                
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