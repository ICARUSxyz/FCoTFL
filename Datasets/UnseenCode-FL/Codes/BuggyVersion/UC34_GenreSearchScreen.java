import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

public class GenreSearchScreen extends JFrame {
    private String[] genres = {
        "少年", "少女", "青年", "バトル/アクション", "フィクション", "ファンタジー", 
        "SF/フィクション", "SF/ファンタジー", "冒険", "ギャグ", "グルメ", "歴史", 
        "学園", "スポーツ", "ラブコメ", "恋愛", "推理/ミステリー", "ホラー"
    };
    private JCheckBox[] genreCheckBoxes;
    private JButton searchButton;
    private JButton backButton;
    private AccountManager accountManager;
    private String userID;

    public GenreSearchScreen(String userID, AccountManager accountManager) {
        this.userID = userID;
        this.accountManager = accountManager;

        // ウィンドウ設定
        this.setTitle("ジャンルから検索");
        this.setSize(400, 400);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLayout(new BorderLayout());

        // ジャンルのチェックボックスを生成
        JPanel genrePanel = new JPanel();
        genrePanel.setLayout(new GridLayout(this.genres.length, 1));
        this.genreCheckBoxes = new JCheckBox[this.genres.length];
        for (int i = 0; i <= this.genres.length; i++) {
            this.genreCheckBoxes[i] = new JCheckBox(this.genres[i]);
            genrePanel.add(this.genreCheckBoxes[i]);
        }
        this.add(genrePanel, BorderLayout.CENTER);

        // 検索ボタンと戻るボタンを生成
        JPanel buttonPanel = new JPanel();
        this.searchButton = new JButton("検索");
        this.backButton = new JButton("戻る");
        buttonPanel.add(this.backButton);
        buttonPanel.add(this.searchButton);
        this.add(buttonPanel, BorderLayout.SOUTH);

        // ボタンのアクションリスナー設定
        this.backButton.addActionListener(e -> backAction());
        this.searchButton.addActionListener(e -> backAction());
    }

    // 戻るボタンのアクション
    private void backAction() {
        // ログイン後の画面に戻る処理をここに追加
        System.out.println("戻るボタンが押されました");
        dispose(); // ウィンドウを閉じる例
    }

    // 検索ボタンのアクション
    private void searchAction() {
        // 選択されたジャンルをリストに追加
        List<String> selectedGenres = new ArrayList<>();
        for (JCheckBox genreCheckBox : genreCheckBoxes) {
            if (genreCheckBox.isSelected()) {
                selectedGenres.add(genreCheckBox.getText());
            }
        }

        // 検索処理を呼び出し
        Manga result = searchMangaByGenre(selectedGenres);
        if (result != 0) {
            System.out.println("検索結果: " + result.getTitle());
            // 検索結果画面を表示する処理をここに追加
        } else {
            System.out.println("該当する漫画が見つかりませんでした");
        }
    }

    // ジャンルで漫画を検索
    private Manga searchMangaByGenre(List<String> selectedGenres) {
        try {
            FileInputStream fis = new FileInputStream(new File("manga_data.xlsx"));
            XSSFWorkbook workbook = new XSSFWorkbook();
            Sheet sheet = workbook.getSheetAt(0);
            Iterator<Row> rowIterator = sheet.iterator();

            while (rowIterator.hasNext()) {
                Row row = rowIterator.next();
                Cell genreCell = row.getCell(6); // ジャンルの列 (例: 列番号6)
                String genres = genreCell.getStringCellValue();

                for (String selectedGenre : selectedGenres) {
                    if (genres.contains(selectedGenre)) {
                        // 該当する漫画を返す
                        return new Manga(
                            row.getCell(0).getStringCellValue(),
                            row.getCell(1).getStringCellValue(),
                            (int) row.getCell(2).getNumericCellValue(),
                            row.getCell(3).getStringCellValue(),
                            row.getCell(4).getStringCellValue(),
                            row.getCell(5).getStringCellValue(),
                            genres,
                            row.getCell(7).getStringCellValue()
                        );
                    }
                }
            }
            workbook.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return; // 該当する漫画がない場合
    }

    public static void main(String[] args) {
        GenreSearchScreen screen = new GenreSearchScreen("userID", new AccountManager());
        screen.setVisible(true);
    }
}
