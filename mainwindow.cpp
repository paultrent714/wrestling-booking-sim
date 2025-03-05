#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "wrestler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Call the database connection method when the MainWindow is created
    connectToDatabase();

    // Ensures the initial page is the landing page
    ui->stackedWidget->setCurrentWidget(ui->LandingPage);

    // Hide navigation buttons that show up on all pages except the game select screen
    ui->RosterTab->hide();
    ui->DashboardTab->hide();
    ui->PromotionTab->hide();
    ui->SettingsTab->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// General buttons to navigate between tabs

void MainWindow::on_DashboardTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Dashboard_Page);
}

void MainWindow::on_PromotionTab_clicked()
{
    if (m_year > 2025 || m_currentWeek > 1 ){
        makeCharts(m_fanHistory, ui->fanChart);
        makeCharts(m_moneyHistory, ui->moneyChart);

    }
    ui->stackedWidget->setCurrentWidget(ui->Promotion_Page);
}

void MainWindow::on_RosterTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Roster_Page);
}

void MainWindow::on_SettingsTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Settings_Page);
}

void MainWindow::on_CardTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Show_Card);
}

void MainWindow::on_RosterDisplayTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->viewRoster);
    populateWrestlerList(m_playerRoster);
}

void MainWindow::on_backToLanding_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->LandingPage);
}

// Loading and creating roster
void MainWindow::on_StartNew_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->newFilePage);
}

void MainWindow::on_defaultRoster_clicked()
{

    newGameSetup();
}

void MainWindow::on_customRoster_clicked()
{
    // Open a file dialog to select the file
    QString filePath = QFileDialog::getOpenFileName(this, "Open Roster File", "", "Text Files (*.txt);;All Files (*)");

    if (filePath.isEmpty()) {
        return;  // If no file is selected, return early
    }

    // Call function to load the data
    loadFromText(filePath);

    if (m_playerRoster.size() < 10){
        QMessageBox::information(this, "Information", "There was not enough valid rows that can be loaded.");
        return;
    }
    newGameSetup();
}

void MainWindow::on_randomRoster_clicked()
{

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 20; ++i){
        Wrestler randomGuy = Wrestler();
        randomGuy.displayInfo();
        m_playerRoster.append(randomGuy);
    }
    newGameSetup();

}

void MainWindow::on_LoadGame_clicked()
{
    // Load wrestler attributes from a text file (provide the correct path)
    loadWrestlerAttributes("savefile.txt"); // replace with actual file path

    ui->stackedWidget->setCurrentIndex(1);
    ui->RosterTab->show();
    ui->DashboardTab->show();
    ui->PromotionTab->show();
    ui->SettingsTab->show();

    updateLabels();
}

void MainWindow::on_userSave_clicked()
{
    // This automatically saves the file in build/Desktop_Qt_6_10_0_MinGW_64_bit-Debug
    saveWrestlerAttributes("saveFile.txt", m_playerRoster);
}

void MainWindow::loadFromText(const QString &filePath) {
    QFile file(filePath);

    // Check if the file can be opened
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open the file. Please check the file format.");
        return;
    }

    QTextStream in(&file);
    m_playerRoster.clear();  // Clear existing roster

    int lineCount = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        lineCount++;

        // Skip empty lines
        if (line.trimmed().isEmpty()) {
            continue;
        }

        // Split the line by tabs (or any other delimiter you expect)
        QStringList fields = line.split(',');  // Use ',' for CSV, or adjust as necessary

        // Ensure the correct number of fields (13 for your case)
        if (fields.size() != 13) {
            QMessageBox::warning(this, "Warning", QString("Line %1 has incorrect number of fields. Skipping this line.").arg(lineCount));
            continue;  // Skip this line if the number of fields is incorrect
        }

        // Parse the fields
        QString name = fields[0];
        int popularity = fields[1].toInt();
        int age = fields[2].toInt();
        int potential = fields[3].toInt();
        int powerhouse = fields[4].toInt();
        int brawler = fields[5].toInt();
        int highFlyer = fields[6].toInt();
        int technician = fields[7].toInt();
        int mma = fields[8].toInt();
        int charisma = fields[9].toInt();
        int stamina = fields[10].toInt();
        int salary = fields[11].toInt();
        int role = fields[12].toInt();

        // Create a new Wrestler object and add it to the list
        Wrestler wrestler(name, popularity, age, potential, powerhouse, brawler, highFlyer, technician,
                          mma, charisma, stamina, salary, role);
        m_playerRoster.append(wrestler);
    }

    file.close();

    if (lineCount == 0) {
        QMessageBox::warning(this, "Warning", "The file is empty.");
    }
}

void MainWindow::connectToDatabase() {
    // Set up SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");  // You can specify a path if needed

    // Open the database
    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError().text();
    }
}

void MainWindow::loadWrestlerAttributes(const QString &filePath) {

    // Assuming the data is loaded from the SQLite database
    QSqlQuery query("SELECT name, popularity, age, potential, powerhouse, brawler, high_flyer, technician, mma, charisma, stamina, salary, role FROM wrestlers");

    // Iterate over the result set and populate the QList with Wrestler objects
    while (query.next()) {
        QString name = query.value(0).toString();
        int popularity = query.value(1).toInt();
        int age = query.value(2).toInt();
        int potential = query.value(3).toInt();
        int powerhouse = query.value(4).toInt();
        int brawler = query.value(5).toInt();
        int highFlyer = query.value(6).toInt();
        int technician = query.value(7).toInt();
        int mma = query.value(8).toInt();
        int charisma = query.value(9).toInt();
        int stamina = query.value(10).toInt();
        int salary = query.value(11).toInt();
        int role = query.value(12).toInt();

        // Create a new Wrestler object and add it to the list
        Wrestler Wrestler(name, popularity, age, potential, powerhouse, brawler, highFlyer, technician,
                          mma, charisma, stamina, salary, role);
        m_playerRoster.append(Wrestler);
    }

}

void MainWindow::saveWrestlerAttributes(const QString &filePath, const QList<Wrestler> &wrestlers) {
    // Get the directory where the executable is located
    QString directory = QCoreApplication::applicationDirPath();
    QString fullFilePath = directory + "/" + filePath;

    QFile file(fullFilePath);

    // Open the file in WriteOnly mode (overwrites existing content)
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open file for writing - " << file.errorString();
        return;
    }
    if (wrestlers.empty()){
        qDebug() << "The list is empty" << filePath;
        return;
    }

    QTextStream out(&file);


    // Iterate through the list and write each wrestler’s attributes as CSV
    for (const Wrestler &wrestler : wrestlers) {
        out << wrestler.name << ","
            << wrestler.popularity << ","
            << wrestler.age << ","
            << wrestler.potential << ","
            << wrestler.powerhouse << ","
            << wrestler.brawler << ","
            << wrestler.highFlyer << ","
            << wrestler.technician << ","
            << wrestler.mma << ","
            << wrestler.charisma << ","
            << wrestler.stamina << ","
            << wrestler.salary << ","
            << wrestler.role << "\n";

        // displays info for debugging
        // wrestler.displayInfo();
    }


    out.flush();
    // Close the file after writing
    file.close();
    qDebug() << "Wrestler data successfully saved to " << filePath;
}

void MainWindow::makeCharts(const QList<int>& values, QWidget* chartWidget) {
    QLineSeries *series = new QLineSeries();

    // Compute actual weeks stored in the values list
    QList<int> weeks;
    for (int i = 0; i < values.size(); ++i) {
        weeks.append(m_currentWeek - (values.size() - 1) + i);
    }

    // Debugging: Print weeks and values
    //qDebug() << "Weeks:" << weeks;
    //qDebug() << "Values:" << values;

    // Add data points using actual weeks
    for (int i = 0; i < values.size(); ++i) {
        //qDebug() << "Appending to series: (" << weeks[i] << "," << values[i] << ")";
        series->append(weeks[i], values[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Last 5 Weeks");

    // Configure X-Axis (Weeks)
    QValueAxis *axisX = new QValueAxis();
    if (!weeks.isEmpty()) {
        axisX->setRange(weeks.first(), weeks.last());  // Ensure continuous range
    }
    axisX->setTickCount(values.size());
    axisX->setTitleText("Weeks");
    axisX->setLabelFormat("%d");  // Ensure integer labels
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configure Y-Axis (Fans/Money)
    QValueAxis *axisY = new QValueAxis();
    int maxValue = values.isEmpty() ? 1 : std::max(1, *std::max_element(values.begin(), values.end()));
    axisY->setRange(0, 1.1 * maxValue);
    axisY->setTitleText(values == m_fanHistory ? "Fans" : "Money");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Set up chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(chartWidget);
    chartView->resize(chartWidget->size());

    if (chartWidget->layout() == nullptr) {
        QVBoxLayout *layout = new QVBoxLayout(chartWidget);
        layout->addWidget(chartView);
        chartWidget->setLayout(layout);
    }

    // Force UI update
    chartView->update();
}

void MainWindow::newGameSetup(){
    // Initialize the game data
    m_money = 10000; // starting value
    m_fans = 100;   // starting value
    m_year = 2025;
    m_currentWeek = 1; // starting week

    // go to dashboard
    ui->stackedWidget->setCurrentWidget(ui->Dashboard_Page);

    // unhide navigation tabs
    ui->RosterTab->show();
    ui->DashboardTab->show();
    ui->PromotionTab->show();
    ui->SettingsTab->show();

    // Ensures all the lists of previous values is set to 0
    m_fanHistory.append(m_fans);
    if (m_fanHistory.size() > 5){
        m_fanHistory.removeAt(0);
    }
    m_moneyHistory.append(m_money);
    if (m_moneyHistory.size() > 5){
        m_moneyHistory.removeAt(0);
    }

    updateLabels();

}

void MainWindow::on_finalizeBooking_clicked()
{
    m_currentWeek++;
    m_money += 1000;
    m_fans += 100;

    if (m_currentWeek >= 53){
        m_year++;
        m_currentWeek = 1;
    }
    m_fanHistory.append(m_fans);
    if (m_fanHistory.size() > 5){
        m_fanHistory.removeAt(0);
    }
    m_moneyHistory.append(m_money);
    if (m_moneyHistory.size() > 5){
        m_moneyHistory.removeAt(0);
    }

    ui->stackedWidget->setCurrentWidget(ui->Dashboard_Page);

    /*
    qDebug() << "week number:" << m_currentWeek;
    qDebug() << "current money: " << m_money;
    qDebug() << "current fans: " << m_fans;
    qDebug() << "Values in fanslist:";
    for (int i = 0; i < m_fanHistory.size(); ++i) {
        qDebug() << "Index" << i << ": " << m_fanHistory[i];
    }
    qDebug() << "Values in money history:";
    for (int i = 0; i < m_moneyHistory.size(); ++i) {
        qDebug() << "Index" << i << ": " << m_moneyHistory[i];
    }
*/

    updateLabels();
}

void MainWindow::updateLabels(){
    ui->fansDisplay->setText("Fans: " + QString::number(m_fans));
    ui->moneyDisplay->setText("Money: $" + QString::number(m_money));
    ui->WeekDisplay->setText("Week: " + QString::number(m_currentWeek));
    ui->yearDisplay->setText("Year: " + QString::number(m_year));
}

void MainWindow::on_pushButton_clicked()
{
    for(int i = 0; i < 26; i++){
        on_finalizeBooking_clicked();
    }

}

void MainWindow::populateWrestlerList(const QList<Wrestler> &wrestlers) {
    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    QHBoxLayout *legendLayout = new QHBoxLayout;
    QLabel *popularityLabel = new QLabel("Popularity");
    QLabel *nameLabel = new QLabel("Name");
    QLabel *roleLabel = new QLabel("Role");

    // Set bold style for legend
    QString legendStyle = "font-weight: bold; text-decoration: underline;";
    popularityLabel->setStyleSheet(legendStyle);
    nameLabel->setStyleSheet(legendStyle);
    roleLabel->setStyleSheet(legendStyle);

    legendLayout->addWidget(popularityLabel);
    legendLayout->addWidget(nameLabel);
    legendLayout->addWidget(roleLabel);

    layout->addLayout(legendLayout); // Add legend as the first row

    for (const Wrestler &wrestler : wrestlers) {
        QHBoxLayout *hLayout = new QHBoxLayout;

        // Popularity Label
        QLabel *popularityValue = new QLabel(QString::number(wrestler.popularity));

        // Create a QPushButton for the wrestler's name (but make it look like a label)
        QPushButton *nameButton = new QPushButton(wrestler.name);

        // Style the button to make it look like clickable text (without background)
        nameButton->setStyleSheet("QPushButton {"
                                  "border: none;"
                                  "background: transparent;"
                                  "text-align: left;"
                                  "color: blue;"
                                  "font-size: 16px;"
                                  "}");
        nameButton->setCursor(Qt::PointingHandCursor); // Set the cursor to hand when hovering

        // Role Label (0 = neutral, 1 = villain, 2 = hero)
        QLabel *roleValue = new QLabel;
        switch (wrestler.role) {
            case 1: roleValue->setText("Villain"); break;
            case 2: roleValue->setText("Hero"); break;
            default: roleValue->setText("Neutral"); break;
        }

        // Connect the button to a slot that updates the wrestler details
        connect(nameButton, &QPushButton::clicked, this, [this, wrestler]() {
            // Switch to the wrestler details page
            ui->stackedWidget->setCurrentIndex(1);  // Assuming index 1 is the viewWrestlerDetails page
            // Update the labels with the selected wrestler's details
            updateWrestlerDetails(wrestler);
        });

        // Add widgets to row layout
        hLayout->addWidget(popularityValue);
        hLayout->addWidget(nameButton);
        hLayout->addWidget(roleValue);

        layout->addLayout(hLayout);
    }

    container->setLayout(layout);
    ui->scrollArea->setWidget(container);
    ui->scrollArea->setWidgetResizable(true);
}


// Function to handle wrestler selection
void MainWindow::showWrestlerDetails(const Wrestler &wrestler) {
    qDebug() << "Displaying details for " << wrestler.name;
}

void MainWindow::updateWrestlerDetails(const Wrestler &wrestler) {
    // Locate the labels inside wrestlerStats' nested layouts
    QLabel *nameLabel = ui->wrestlerStats->findChild<QLabel *>("nameLabel");
    QLabel *ageLabel = ui->wrestlerStats->findChild<QLabel *>("ageLabel");
    QLabel *popularityLabel = ui->wrestlerStats->findChild<QLabel *>("popularityLabel");
    QLabel *staminaLabel = ui->wrestlerStats->findChild<QLabel *>("staminaLabel");
    QLabel *powerhouseLabel = ui->wrestlerStats->findChild<QLabel *>("powerhouseLabel");

    // Set the wrestler's details into the labels
    nameLabel->setText(wrestler.name);
    ageLabel->setText(QString::number(wrestler.age));
    popularityLabel->setText(QString::number(wrestler.popularity ));
    staminaLabel->setText(QString::number(wrestler.stamina));
    powerhouseLabel->setText(QString::number(wrestler.powerhouse));
}

