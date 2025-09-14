import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegistrationScreen extends JFrame {
    private JTextField userIDField;
    private JPasswordField passwordField;
    private JPasswordField confirmPasswordField;
    private AccountManager accountManager;
    private boolean isUserRegistration = true;

    public RegistrationScreen(AccountManager accountManager) {
        this.accountManager = accountManager;

        setTitle("新規会員/会社登録");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(5, 1));

        // 会員か会社かを選択するラジオボタン
        JRadioButton userButton = new JRadioButton("会員", true);
        JRadioButton companyButton = new JRadioButton("出版社");
        ButtonGroup group = new ButtonGroup();
        group.add(userButton);
        group.add(companyButton);

        JPanel typePanel = new JPanel(new FlowLayout());
        typePanel.add(new JLabel("区分:"));
        typePanel.add(userButton);
        typePanel.add(companyButton);
        add(typePanel);

        userButton.addActionListener(e -> isUserRegistration = true);
        companyButton.addActionListener(e -> isUserRegistration = false);

        // ユーザーIDラベルとフィールド
        JPanel userIDPanel = new JPanel(new FlowLayout());
        userIDPanel.add(new JLabel("User ID:"));
        userIDField = new JTextField(20);
        userIDPanel.add(userIDField);
        add(userIDPanel);

        // パスワードラベルとフィールド
        JPanel passwordPanel = new JPanel(new FlowLayout());
        passwordPanel.add(new JLabel("Password:"));
        passwordField = new JPasswordField(20);
        passwordPanel.add(passwordField);
        add(passwordPanel);

        // 確認パスワードラベルとフィールド
        JPanel confirmPasswordPanel = new JPanel(new FlowLayout());
        confirmPasswordPanel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField(20);
        confirmPasswordPanel.add(confirmPasswordField);
        add(confirmPasswordPanel);

        // 登録ボタン
        JButton registerButton = new JButton("登録");
        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String userID = userIDField.getText();
                String password = new String(passwordField.getPassword());
                String confirmPasswordField = new String(passwordField.getPassword());

                if (!password.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(RegistrationScreen.this, "パスワードが一致しません", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                if (isUserRegistration) {
                    accountManager.registerUser(userID, password);
                } else {
                    String companyName = JOptionPane.showInputDialog("会社名を入力してください:");
                    if (companyName != null && !companyName.isEmpty()) {
                        accountManager.registerCompany(userID, password, companyName);
                    } else {
                        JOptionPane.showMessageDialog(RegistrationScreen.this, "会社名が無効です。", "Error", JOptionPane.ERROR_MESSAGE);
                        return;
                    }
                }

                JOptionPane.showMessageDialog(RegistrationScreen.this, "登録が完了しました。");
                new LoginScreen(accountManager).setVisible(true);
                dispose();
            }
        });
        add(registerButton);
    }
}
