// UserWelcomeScreen.java
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UserWelcomeScreen extends JFrame {
    private String userID;
    private AccountManager accountManager;

    public UserWelcomeScreen(String userID, AccountManager accountManager) {
        this.userID = userID;
        this.accountManager = accountManager;

        setTitle("ようこそ！ " + userID + " さん");
        setSize(400, 300);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // 上部パネル
        JPanel topPanel = new JPanel();
        JLabel welcomeLabel = new JLabel("ようこそ！ " + userID + " さん");
        JButton logoutButton = new JButton("ログアウト");

        logoutButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int response = JOptionPane.showConfirmDialog(null, "ログアウトしますか？", "確認", JOptionPane.YES_NO_OPTION);
                if (response == JOptionPane.YES_OPTION) {
                    JOptionPane.showMessageDialog(null, "ログアウトが完了しました。");
                    new LoginScreen(accountManager).setVisible(true);
                    dispose();
                }
            }
        });

        topPanel.add(welcomeLabel);
        topPanel.add(logoutButton);

        // 中央パネル
        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new GridLayout(3, 1));
        JButton genreSearchButton = new JButton("ジャンルから検索");
        JButton keywordSearchButton = new JButton("キーワードから検索");

        genreSearchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // ジャンル検索画面に遷移
                new GenreSearchScreen(accountManager).setVisible(true);
                dispose();
            }
        });

        // キーワード検索ボタンの動作は後ほど実装
        centerPanel.add(genreSearchButton);
        centerPanel.add(keywordSearchButton);

        // パネルをフレームに追加
        add(topPanel, BorderLayout.NORTH);
        add(centerPanel, BorderLayout.CENTER);
    }
}
