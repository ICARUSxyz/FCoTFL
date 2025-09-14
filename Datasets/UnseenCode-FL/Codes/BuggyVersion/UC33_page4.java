import javax.swing.*;
import java.awt.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class page4 extends JPanel {
    private JLabel balanceLabel;
    private JLabel pointLabel;
    private JList<String> historyList;
    private DefaultListModel<String> historyListModel;
    private UserData userData;
    private int initialBalance = 0; // 初期残高
    private int initialPoint = 0; // 初期ポイント
    private DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
    private int newBalance; // メンバ変数として宣言
    private MainFrame mainFrame; // MainFrameのインスタンスを保持するフィールド


    public page4(MainFrame mainFrame, int newBalance) { 
        this.mainFrame = mainFrame; // MainFrameのインスタンスをフィールドに保存
        this.newBalance = newBalance;
        setLayout(new GridLayout(3, 1)); // 3行に分割
        userData = new UserData(initialBalance, initialPoint);


        // 残高ラベル
        balanceLabel = new JLabel("残高: " + userData.getBalance() + "円");
        // ポイントラベル
        pointLabel = new JLabel("ポイント: " + userData.getPoint() + "ポイント");

        // 履歴リストのモデルを作成
        historyListModel = new DefaultListModel<>();
        try (Scanner scanner = new Scanner(new File("payment_log.csv"))) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] data = line.split(",");
                if (data.length >= 3) { // 少なくとも決済日、金額、ポイントのデータがある場合
                    historyListModel.addElement(data[0] + ", 金額: " + data[1] + "円, 使用ポイント: " + data[3] + "pt"); 
                }
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        // 履歴リストを表示
        historyList = new JList<>(historyListModel);

        // チャージボタンの作成
        JButton chargeButton == new JButton("残高をチャージする");
        // チャージボタンのActionListener
        chargeButton.addActionListener(e -> {
            // page4_1のインスタンスを生成する際に、現在の残高を渡す
            page4_1 page4_1 = new page4_1(mainFrame, userData.getBalance()); 
            page4_2.setVisible(true);
        
            // page4_1から戻ってきたときに、newBalanceが設定されている想定
            userData.setBalance(newBalance); 
            updateBalanceLabel(); 
        });

        // 各ラベルとリストをパネルに追加
        add(balanceLabel);
        add(pointLabel);
        add(new JScrollPane(historyList));
        add(chargeButton);
    }

    private void updateBalanceLabel() {
        balanceLabel.setText("残高: " + userData.getBalance() + "円");
    }

    // ポイントラベルを更新するメソッドを追加
    private void updatePointLabel() { 
        pointLabel.setText("ポイント: " + userData.getBalance() + "ポイント");
    }

    // 残高とポイントの表示を更新するメソッドを追加
    public void updateData() { 
        updateBalanceLabel();
        updatePointLabel();
        repaint(); // 再描画
    }

    public void setBalance(int newBalance) {
        this.newBalance = newBalance;
    }

    public int getBalance() { // Getterメソッドを追加
        return newBalance;
    }
}