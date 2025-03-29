#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "wrestler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Call the database connection method when the MainWindow is created
    //connectToDatabase();

    dataManager = new GameDataManager();
    dataManager->openDatabase();

    // Ensures the initial page is the landing page
    ui->stackedWidget->setCurrentWidget(ui->LandingPage);

    // Hide navigation buttons that show up on all pages except the game select screen
    ui->RosterTab->hide();
    ui->DashboardTab->hide();
    ui->PromotionTab->hide();
    ui->SettingsTab->hide();


    ui->sortByAttributesCB->addItems({"Name", "Popularity", "Stamina",
                                      "Age", "Salary", "Role", "Gender", "Charisma"});
}

MainWindow::~MainWindow()
{
    dataManager->closeDatabase();
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
    populateMatchList();
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
void MainWindow::on_ChampionTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->ChampionshipPage);
    setUpChampionSelection();
}
void MainWindow::on_TeamsTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->tagTeamPage);
    populateTeamList();
}
void MainWindow::on_nextWeekButton_clicked()
{
    m_currentWeek++;

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

    updateDashboardLabels();
    ui->stackedWidget->setCurrentWidget(ui->Dashboard_Page);
    m_currentShow.clear();
}
// Skips 26 weeks; used mainly for debugging
void MainWindow::on_pushButton_clicked()
{
    for(int i = 0; i < 26; i++){
        on_finalizeBooking_clicked();
    }

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

    m_lastUsedID = 1;
    for (int i = 0; i < 20; ++i){
        Wrestler randomGuy = Wrestler(m_lastUsedID);
        randomGuy.displayInfo();
        m_lastUsedID++;
        m_playerRoster.append(randomGuy);
    }
    newGameSetup();
}
void MainWindow::on_LoadGame_clicked()
{
    // Load wrestlers and store them in m_playerRoster
    dataManager->loadWrestlers();
    m_playerRoster = dataManager->getWrestlers();

    // Load championships, then store them in m_world, m_tag, and m_women
    dataManager->loadChampionships();
    QList<championship> championshipsList = dataManager->getChampionships();
    // Check if the list is not empty and has the expected number of championships
    if (championshipsList.size() >= 3) {
        m_world = championshipsList[0];
        m_tag = championshipsList[1];
        m_women = championshipsList[2];
    }
    // Load teams and store them in m_teams
    dataManager->loadTeams(m_teams);
    // Load game info and store it in m_money, m_fans, m_year, m_currentWeek, etc.
    dataManager->loadGameInfo(m_money, m_fans, m_year, m_currentWeek, m_moneyHistory, m_fanHistory);
    // Load the current show and store it in m_currentShow
    dataManager->loadShow(m_currentShow);

    ui->stackedWidget->setCurrentWidget(ui->Dashboard_Page);
    ui->RosterTab->show();
    ui->DashboardTab->show();
    ui->PromotionTab->show();
    ui->SettingsTab->show();

    updateDashboardLabels();
}
void MainWindow::on_userSave_clicked()
{

    // Load game data into member variables using the GameDataManager
    dataManager->saveWrestlers(m_playerRoster);          // Load wrestlers into m_playerRoster
    dataManager->saveChampionships(m_world, m_tag, m_women); // Load championships
    dataManager->saveTeams(m_teams);                      // Load teams
    dataManager->saveGameInfo(m_money, m_fans, m_year, m_currentWeek, m_moneyHistory, m_fanHistory); // Load game-specific info
    dataManager->saveShow(m_currentShow);                 // Load current show data

    // Set the last used ID (assuming it is saved in the database or calculated from the loaded data)
    m_lastUsedID = m_playerRoster.size() + 1;  // or another approach to set the last ID
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
        bool gender = fields[1].toInt();
        int popularity = fields[2].toInt();
        int age = fields[3].toInt();
        int potential = fields[4].toInt();
        int powerhouse = fields[5].toInt();
        int brawler = fields[6].toInt();
        int highFlyer = fields[7].toInt();
        int technician = fields[8].toInt();
        int mma = fields[9].toInt();
        int charisma = fields[10].toInt();
        int stamina = fields[11].toInt();
        int salary = fields[12].toInt();
        int role = fields[13].toInt();

        // Create a new Wrestler object and add it to the list
        Wrestler wrestler(lineCount, name, gender, popularity, age, potential, powerhouse, brawler, highFlyer, technician,
                          mma, charisma, stamina, salary, role);
        m_playerRoster.append(wrestler);
    }

    file.close();

    if (lineCount == 0) {
        QMessageBox::warning(this, "Warning", "The file is empty.");
    }
}

void MainWindow::makeCharts(const QList<int>& values, QWidget* chartWidget) {
    QLineSeries *series = new QLineSeries();

    // Compute actual weeks stored in the values list
    QList<int> weeks;
    for (int i = 0; i < values.size(); ++i) {
        weeks.append(m_currentWeek - (values.size() - 1) + i);
    }

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
    m_money = 1000000; // starting value of 1 mil
    m_fans = 1000;   // starting value
    m_year = 2025;
    m_currentWeek = 1; // starting week

    // adds default championships to list
    m_world = championship("World Championship", false, false); // Single
    m_tag = championship("Tag Team Championship", true, false); // Tag
    m_women = championship("Women's Championship", false, true); // Women's

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

    updateDashboardLabels();

}

// Shows results of a show
void MainWindow::on_finalizeBooking_clicked()
{
    // Set ratings for each match and update championships if necessary
    for ( match &m : m_currentShow.getMatchesEdit()) {
        m.calcMatchRating(m.getParticipants());

        // Apply title change for each championship if applicable
        if (m.isChampionship()) {

            m.applyTitleChange(&m_world);  // For world championship
            m.applyTitleChange(&m_tag);    // For tag team championship
            m.applyTitleChange(&m_women);  // For women's championship

        }
    }

    // Calculates values for the show
    m_currentShow.calculateShowRating();
    m_currentShow.calculateCosts();
    m_currentShow.calculateFanImpact(m_fans);
    m_currentShow.calculateShowRevenue(m_fans);

    // updates fans and money values
    m_money += m_currentShow.getTotalRevenue() - m_currentShow.getTotalCosts();
    m_fans += m_currentShow.getFanImpact();

    ui->WeekDisplay->setText("Year" + QString::number(m_year) + "Week " + QString::number(m_currentWeek));

    ui->showRatingLabel->setText("Show Rating: " + QString::number(m_currentShow.getShowRating(), 'f', 2) );
    ui->fansChangeLabel->setText("Fans Change: " + QString::number(m_currentShow.getFanImpact()));
    ui->resultFanLabel->setText("Total Fans: " + QString::number(m_fans));
    ui->showRevenueLabel->setText("Show Revenue: " + QString::number(m_currentShow.getTotalRevenue()));
    ui->showCostsLabel->setText("Show Costs: " + QString::number(m_currentShow.getTotalCosts()));
    ui->showProfitLabel->setText("Show Profit: " +
                                 QString::number(m_currentShow.getTotalRevenue() - m_currentShow.getTotalCosts()));
    ui->resultMoneyLabel->setText("Total Money: " + QString::number(m_money));

    ui->stackedWidget->setCurrentWidget(ui->showResults);
    populateResultsList();  // shows matches and their results


}
void MainWindow::populateResultsList(){
    QList<match>& matches = m_currentShow.getMatchesEdit();

    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    for (int i = 0; i < matches.size(); ++i) {
        match& m = matches[i];

        QHBoxLayout *hLayout = new QHBoxLayout;

        // Match type
        QLabel *matchTypeLabel = new QLabel(m.getMatchType());
        matchTypeLabel->setStyleSheet("color: black;");

        // Participants list
        QString participantsList;
        for (Wrestler* wrestler : m.getParticipants()) {
            if (wrestler) {
                if (!participantsList.isEmpty()) {
                    participantsList += ", ";
                }
                participantsList += wrestler->getName();
            }
        }
        QLabel *participantsLabel = new QLabel(participantsList);
        participantsLabel->setStyleSheet("color: black;");

        // Winner label
        QLabel *winnerLabel = new QLabel("Winner: " + m.getWinner()->getName());
        winnerLabel->setStyleSheet("color: black;");

        // Rating label
        QLabel *ratingLabel = new QLabel("⭐ " + QString::number(m.getRating(), 'f', 1));
        ratingLabel->setStyleSheet("color: black;");

        // Layout
        hLayout->addWidget(matchTypeLabel);
        hLayout->addWidget(participantsLabel);
        hLayout->addWidget(winnerLabel);
        hLayout->addWidget(ratingLabel);

        layout->addLayout(hLayout);
    }

    container->setLayout(layout);
    ui->matchResults->setWidget(container);  // Assign to the results scroll area
    ui->matchResults->setWidgetResizable(true);
}

void MainWindow::updateDashboardLabels(){
    ui->fansDisplay->setText("Fans: " + QString::number(m_fans));
    ui->moneyDisplay->setText("Money: $" + QString::number(m_money));
    ui->WeekDisplay->setText("Week: " + QString::number(m_currentWeek));
    ui->yearDisplay->setText("Year: " + QString::number(m_year));
}

void MainWindow::populateWrestlerList(const QList<Wrestler> &wrestlers) {
    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    QHBoxLayout *legendLayout = new QHBoxLayout;
    QLabel *popularityLabel = new QLabel("Popularity");
    QLabel *nameLabel = new QLabel("Name");
    QLabel *ageLabel = new QLabel("Age");
    QLabel *roleLabel = new QLabel("Role");

    // Set bold style for legend
    QString legendStyle = "font-weight: bold; text-decoration: underline;";
    popularityLabel->setStyleSheet(legendStyle);
    nameLabel->setStyleSheet(legendStyle);
    roleLabel->setStyleSheet(legendStyle);

    legendLayout->addWidget(popularityLabel);
    legendLayout->addWidget(nameLabel);
    legendLayout->addWidget(roleLabel);
    legendLayout->addWidget(ageLabel);

    layout->addLayout(legendLayout); // Add legend as the first row

    for (const Wrestler &wrestler : wrestlers) {
        QHBoxLayout *hLayout = new QHBoxLayout;

        // Popularity Label
        QLabel *popularityValue = new QLabel(QString::number(wrestler.getPopularity()));

        // Create a QPushButton for the wrestler's name (but make it look like a label)
        QPushButton *nameButton = new QPushButton(wrestler.getName());

        // Style the button to make it look like clickable text (without background)
        nameButton->setStyleSheet("QPushButton {"
                                  "border: none;"
                                  "background: transparent;"
                                  "text-align: left;"
                                  "color: blue;"
                                  "font-size: 16px;"
                                  "}");
        nameButton->setCursor(Qt::PointingHandCursor); // Set the cursor to hand when hovering

        QLabel *ageValue = new QLabel(QString::number(wrestler.getAge()));

        // Role Label (0 = neutral, 1 = villain, 2 = hero)
        QLabel *roleValue = new QLabel;
        switch (wrestler.getRole()) {
            case 1: roleValue->setText("Villain"); break;
            case 2: roleValue->setText("Hero"); break;
            default: roleValue->setText("Neutral"); break;
        }

        // Connect the button to a slot that updates the wrestler details
        connect(nameButton, &QPushButton::clicked, this, [this, wrestler]() {
            // Switch to the wrestler details page
            ui->stackedWidget->setCurrentWidget(ui->wrestlerStats);
            // Update the labels with the selected wrestler's details
            updateWrestlerDetails(wrestler);
        });

        // Add widgets to row layout
        hLayout->addWidget(popularityValue);
        hLayout->addWidget(nameButton);
        hLayout->addWidget(roleValue);
        hLayout->addWidget(ageValue);

        layout->addLayout(hLayout);
    }

    container->setLayout(layout);
    ui->scrollArea->setWidget(container);
    ui->scrollArea->setWidgetResizable(true);
}
void MainWindow::updateWrestlerDetails(const Wrestler &wrestler) {

    ui->nameLabel->setText(wrestler.getName());


    ui->ageLabel->setText("Age: " + QString::number(wrestler.getAge()));

    ui->powerhouseLabel->setText("Powerhouse: " + QString::number(wrestler.getPowerhouse()));
    ui->brawlerLabel->setText("Brawler: " + QString::number(wrestler.getBrawler()));
    ui->highFlyerLabel->setText("High Flyer: " + QString::number(wrestler.getHighFlyer()));
    ui->technicianLabel->setText("Technician: " + QString::number(wrestler.getTechnician()));
    ui->mmaLabel->setText("MMA: " + QString::number(wrestler.getMMA()));

    ui->populatiryLabel->setText("Popularity: " + QString::number(wrestler.getPopularity()));
    ui->charismaLabel->setText("Charisma: " + QString::number(wrestler.getCharisma()));
    ui->staminaLabel->setText("Stamina: " + QString::number(wrestler.getStamina()));

    ui->salaryLabel->setText("Salary: $" + QString::number(wrestler.getSalary()));

    // EDIT WEEKS REMAINING!! RN I DO NOT HAVE THAT IMPLEMENTED
    ui->matchesRemainingLabel->setText("Matches Remaining: " +QString::number(wrestler.getSalary()));

    QString roleText;
    switch (wrestler.getRole()) {
    case 1: roleText = "Villain"; break;
    case 2: roleText = "Hero"; break;
    default: roleText = "Neutral"; break;
    }
    ui->roleLabel->setText("Role: " + roleText);

    // Set genderLabel based on wrestler.gender (0 = M, 1 = F)
    QString genderText = wrestler.getGender() ? "F" : "M";
    ui->genderLabel->setText("Gender: " + genderText);

}

// Functions that show list of matches on show and edit matches
void MainWindow::populateMatchList( ) {
    ui->stackedWidget->setCurrentWidget(ui->Show_Card);
    QList<match>& matches = m_currentShow.getMatchesEdit();

    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    for (int i = 0; i < matches.size(); ++i) {
        match& m = matches[i];

        QHBoxLayout *hLayout = new QHBoxLayout;

        // Display match type, participants, rating, etc.
        QLabel *matchTypeValue = new QLabel(m.getMatchType());
        QString participantsList;
        for (Wrestler* wrestler : m.getParticipants()) {
            if (wrestler) {  // Check if the pointer is not null
                if (!participantsList.isEmpty()) {
                    participantsList += ", ";  // Add a separator between names
                }
                participantsList += wrestler->getName();  // Get the name of the wrestler
            }
        }

        QLabel *participantsValue = new QLabel(participantsList);

        QLabel *ratingValue = new QLabel(QString::number(m.getRating()) + " ★");

        // Edit Button
        QPushButton *editButton = new QPushButton("Edit");
        connect(editButton, &QPushButton::clicked, this, [this, &m, i ]() {
            openEditMatchPage(m, i);
        });

        // Remove Button
        QPushButton *removeButton = new QPushButton("Remove");
        connect(removeButton, &QPushButton::clicked, this, [this, i]() {
            m_currentShow.removeMatch(i);  // Remove match by index
            populateMatchList();
        });

        hLayout->addWidget(matchTypeValue);
        hLayout->addWidget(participantsValue);
        hLayout->addWidget(ratingValue);
        hLayout->addWidget(editButton);
        hLayout->addWidget(removeButton);

        layout->addLayout(hLayout);
    }

    container->setLayout(layout);
    ui->matchScrollArea->setWidget(container);
    ui->matchScrollArea->setWidgetResizable(true);
}
void MainWindow::openEditMatchPage(match& m, int index)
{
    m_currentMatch = &m; // Store a pointer to the current match being edited
    m_currentMatchIndex = index;  // Store index for updating later

    ui->stackedWidget->setCurrentWidget(ui->matchSetup); // Switch to the match edit page

    // Set match type (stipulation)
    ui->matchTypeComboBox->setCurrentText(m.getMatchType());

    // Clear existing wrestler selection
    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
    if (wrestlerLayout) {
        while (wrestlerLayout->count() > 0) {
            QWidget* widget = wrestlerLayout->itemAt(0)->widget();
            wrestlerLayout->removeWidget(widget);
            delete widget;
        }
    }

    // Populate wrestler selection combo boxes and add remove buttons for each participant
    for (Wrestler* wrestler : m.getParticipants()) {
        // Create a new ComboBox for the wrestler
        QComboBox* wrestlerComboBox = new QComboBox(this);
        wrestlerComboBox->addItem(wrestler->getName()); // Add the wrestler's name
        wrestlerComboBox->setStyleSheet(
            "QComboBox { background: #f0f0f0; border: 1px solid #888; padding: 4px; border-radius: 4px; color: black; }"
            "QComboBox::drop-down { width: 20px; border-left: 1px solid #888; background: #d3d3d3; }"
            "QComboBox::down-arrow { image: url(:/icons/down-arrow.png); width: 12px; height: 12px; }"
            "QComboBox QAbstractItemView { background: #f0f0f0; selection-background-color: #0078D7; color: black; border: 1px solid #888; }"
            );
        wrestlerComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


        // Create a new Remove button for the wrestler
        QPushButton* removeButton = new QPushButton("Remove", this);
        connect(removeButton, &QPushButton::clicked, this, [this, wrestlerComboBox]() {
            removeWrestlerFromMatch(wrestlerComboBox);  // Remove the selected wrestler ComboBox
        });
        // Remove button style is visible
        removeButton->setStyleSheet(
            "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;"
        );

        // Add the ComboBox and Remove button to the layout
        QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
        int row = wrestlerLayout->rowCount();
        wrestlerLayout->addWidget(wrestlerComboBox, row, 0);
        wrestlerLayout->addWidget(removeButton, row, 1);

        // Connect the ComboBox to updateMatchWrestlerSelection function
        connect(wrestlerComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updateMatchWrestlerSelection);
    }

    // Set the winner combobox selection
    if (m.getWinner()) {
        QString winnerName = m.getWinner()->getName();
        ui->winnerComboBox->setCurrentText(winnerName);
    } else {
        ui->winnerComboBox->setCurrentIndex(ui->winnerComboBox->findText("Random Winner")); // Set to "Random Winner" if no winner
    }


    // Set checkboxes for whether tag/ championship match is scheduled
    ui->champCheckBox->setChecked(m.isChampionship());
    ui->teamCheckBox->setChecked(m.isTeam());
}
void MainWindow::on_addMatchButton_clicked()
{
    match newMatch;
    newMatch.setMatchType("Standard");

    m_currentShow.addMatch(newMatch);

    populateMatchList();
}
void MainWindow::on_addToMatch_clicked() {
    // Ensure participantLayout has a valid layout (initialized only once)
    if (!ui->participantLayout->layout()) {
        ui->participantLayout->setLayout(new QGridLayout);  // Initialize layout if not done yet
    }

    // Check if there are already 10 participants in the match (10 combo boxes and 10 buttons)
    QGridLayout* participantLayout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
    if (participantLayout->count() >= 20) {
        // Show a message saying you can't add more participants
        QMessageBox::information(this, "Limit Reached", "A match can have a maximum of 10 participants.");
        return;  // Exit the function if the limit is reached
    }

    // Create a new ComboBox for selecting a wrestler
    QComboBox* wrestlerComboBox = new QComboBox(this);

    // Get currently selected wrestlers to avoid duplicates
    QSet<QString> selectedWrestlers;
    for (int i = 0; i < participantLayout->count(); ++i) {
        QComboBox* existingCombo = qobject_cast<QComboBox*>(participantLayout->itemAt(i)->widget());
        if (existingCombo) {
            selectedWrestlers.insert(existingCombo->currentText());
        }
    }

    // Populate with available wrestlers
    QStringList wrestlerNames;
    for (const Wrestler& wrestler : m_playerRoster) {
        if (!selectedWrestlers.contains(wrestler.getName())) {
            wrestlerNames.append(wrestler.getName());
        }
    }

    // Add check to ensure there's at least one wrestler
    if (wrestlerNames.isEmpty()) {
        return;  // Avoid adding a wrestler if there are no available wrestlers
    }

    wrestlerComboBox->addItems(wrestlerNames);

    // ComboBox style is visible
    wrestlerComboBox->setStyleSheet(
        "QComboBox { background: #f0f0f0; border: 1px solid #888; padding: 4px; border-radius: 4px; color: black; }"
        "QComboBox::drop-down { width: 20px; border-left: 1px solid #888; background: #d3d3d3; }"
        "QComboBox::down-arrow { image: url(:/icons/down-arrow.png); width: 12px; height: 12px; }"
        "QComboBox QAbstractItemView { background: #f0f0f0; selection-background-color: #0078D7; color: black; border: 1px solid #888; }"
        );
    wrestlerComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Add the ComboBox to the layout
    int row = participantLayout->rowCount();
    participantLayout->addWidget(wrestlerComboBox, row, 0);

    // Connect the ComboBox to updateMatchWrestlerSelection
    connect(wrestlerComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updateMatchWrestlerSelection);

    // Create and configure the Remove button for the wrestler
    QPushButton* removeButton = new QPushButton("Remove", this);
    connect(removeButton, &QPushButton::clicked, this, [this, wrestlerComboBox]() {
        removeWrestlerFromMatch(wrestlerComboBox);  // Remove the selected wrestler ComboBox
    });

    // Remove button is visible
    removeButton->setStyleSheet(
        "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;"
        );

    // Add the Remove button next to the ComboBox in the same row
    participantLayout->addWidget(removeButton, row, 1);

    // Ensure that the layout has been properly updated
    participantLayout->update();  // Refresh layout after adding the widgets

    // Update the Save button status based on the number of wrestlers
    updateSaveMatchButton();
    updateMatchWrestlerSelection();
}
void MainWindow::removeWrestlerFromMatch(QComboBox* wrestlerComboBox) {
    if (!wrestlerComboBox) return;

    QGridLayout* participantLayout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
    if (!participantLayout) return;

    int indexToRemove = -1;

    // Find the index of the ComboBox
    for (int i = 0; i < participantLayout->count(); ++i) {
        QWidget* widget = participantLayout->itemAt(i)->widget();
        if (widget == wrestlerComboBox) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        // Remove and delete the combo box
        QWidget* comboWidget = participantLayout->itemAt(indexToRemove)->widget();
        participantLayout->removeWidget(comboWidget);
        delete comboWidget;

        // Remove and delete the corresponding remove button
        QWidget* buttonWidget = participantLayout->itemAt(indexToRemove)->widget();
        if (buttonWidget) {
            participantLayout->removeWidget(buttonWidget);
            delete buttonWidget;
        }
    }
    updateMatchWrestlerSelection();
    updateSaveMatchButton();
}
void MainWindow::updateSaveMatchButton(){
    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
    QSet<QString> uniqueWrestlers;  // To track unique wrestlers

    if (wrestlerLayout) {
        // Iterate through all items in the layout and add the wrestler names to the set
        for (int i = 0; i < wrestlerLayout->count(); ++i) {
            QComboBox* comboBox = qobject_cast<QComboBox*>(wrestlerLayout->itemAt(i)->widget());
            if (comboBox) {
                QString wrestlerName = comboBox->currentText();
                if (!wrestlerName.isEmpty()) {
                    uniqueWrestlers.insert(wrestlerName);  // Add wrestler name to set
                }
            }
        }
    }

    // Enable the save button only if at least 2 different wrestlers are added
    ui->saveMatchDetails->setEnabled(uniqueWrestlers.size() >= 2);
}
void MainWindow::updateMatchWrestlerSelection() {
    if (!m_currentMatch) return;

    QSet<QString> selectedWrestlers;
    QGridLayout* layout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
    if (!layout) return;

    m_currentMatch->clearParticipants();
    for (int i = 0; i < layout->count(); ++i) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(layout->itemAt(i)->widget());
        if (comboBox) {
            QString wrestlerName = comboBox->currentText();
            for (Wrestler& wrestler : m_playerRoster) {
                if (wrestler.getName() == wrestlerName) {
                    m_currentMatch->addWrestler(&wrestler);
                    selectedWrestlers.insert(wrestlerName);
                    break;
                }
            }
        }
    }

    // Update the winnerComboBox
    ui->winnerComboBox->clear();
    // Add the "Random" option to the winnerComboBox
    ui->winnerComboBox->addItem("Random");

    for (Wrestler* wrestler : m_currentMatch->getParticipants()) {
        ui->winnerComboBox->addItem(wrestler->getName());
    }

    // Updates layout if tag team match
    if (ui->teamCheckBox->isChecked()) {
        updateTeamMatchLayout(true);  // Call function to update layout for team match
    }
}
void MainWindow::on_saveMatchDetails_clicked() {
    if (!m_currentMatch) return;

    QString matchType = ui->matchTypeComboBox->currentText();
    m_currentMatch->setMatchType(matchType);

    // Set championship status
    m_currentMatch->setChampionship(ui->champCheckBox->isChecked());

    // Set tag match status
    m_currentMatch->setTag(ui->teamCheckBox->isChecked());

    clearTeamMatchSpacer();

    // Check if the winner is selected as "Random"
    if (ui->winnerComboBox->currentText() == "Random") {
        m_currentMatch->setWinner(m_currentMatch->randomWinner());  // Set a random winner
    }
    else {
    // Otherwise, set the winner based on the ComboBox selection
        QString winnerName = ui->winnerComboBox->currentText();
        for (Wrestler& wrestler : m_playerRoster) {
            if (wrestler.getName() == winnerName) {
                m_currentMatch->setWinner(&wrestler);
                break;
            }
        }
    }
    ui->stackedWidget->setCurrentWidget(ui->Show_Card);
    populateMatchList();
}
//For tag team matches
void MainWindow::on_teamCheckBox_toggled(bool checked)
{
    updateTeamMatchLayout(checked);
}
void MainWindow::updateTeamMatchLayout(bool isTeamMatch) {
    QGridLayout* layout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());

    if (!layout) return; // Ensure layout exists

    // Get number of wrestler widgets
    int wrestlerCount = 0;
    for (int i = 0; i < layout->count(); ++i) {
        QWidget* widget = layout->itemAt(i)->widget();
        // Assuming wrestlers are combo boxes, count them
        if (qobject_cast<QComboBox*>(widget)) {
            wrestlerCount++;
        }
    }

    // Apply color split style
    if (isTeamMatch) {
        ui->participantLayout->setStyleSheet(
            "background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
            "stop:0 #A3C6FF, stop:0.49 #A3C6FF, stop:0.50 #FFB3B3, stop:1 #FFB3B3);"
            );
    } else { ui->participantLayout->setStyleSheet(""); }

    // Remove any existing spacer
    if (m_spacerItem != nullptr ) {
        layout->removeItem(m_spacerItem);
        delete m_spacerItem;
        m_spacerItem = nullptr;
    }

    // If odd number of wrestlers, add a spacer at the bottom
    if (isTeamMatch && wrestlerCount % 2 == 1) {
        // Try to get the height of the first combo box
        int comboBoxHeight = 0;
        if (layout->count() > 0) {
            QWidget* firstItemWidget = layout->itemAt(0)->widget();
            if (qobject_cast<QComboBox*>(firstItemWidget)) {
                comboBoxHeight = firstItemWidget->height(); // Get the height of the first combo box
            }
        }

        // Spacer the slighlty taller than height of the combo boxes
        m_spacerItem = new QSpacerItem(0, comboBoxHeight * 1.3, QSizePolicy::Minimum, QSizePolicy::Fixed);

        int row = layout->rowCount();
        // Insert spacer at the last row
        layout->addItem(m_spacerItem, row, 0); // Add spacer at the end
    }
}
void MainWindow::clearTeamMatchSpacer() {
    if (m_spacerItem != nullptr) {
        QGridLayout* layout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
        if (layout) {
            layout->removeItem(m_spacerItem);
        }
        delete m_spacerItem;
        m_spacerItem = nullptr;
    }
}


//For champions page
void MainWindow::setUpChampionSelection() {

    // Initially disconnect combo boxes so champion will not be set to vacant/ first option added in combobox
    disconnect(ui->worldChampComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onWorldChampSelected);
    disconnect(ui->teamComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onTagChampSelected);
    disconnect(ui->tagChampComboBox1, &QComboBox::currentIndexChanged, this, &MainWindow::onManualTagChampsSelected);
    disconnect(ui->tagChampComboBox2, &QComboBox::currentIndexChanged, this, &MainWindow::onManualTagChampsSelected);
    disconnect(ui->womenChampComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onWomenChampSelected);

    // No champion selected
    ui->worldChampComboBox->addItem("Vacant", QVariant());
    ui->tagChampComboBox1->addItem("Vacant", QVariant());
    ui->tagChampComboBox2->addItem("Vacant", QVariant());
    ui->womenChampComboBox->addItem("Vacant", QVariant());

    for (const Wrestler& wrestler : m_playerRoster) {
        QVariant data = QVariant::fromValue(const_cast<Wrestler*>(&wrestler));

        // Add to all relevant combo boxes
        ui->worldChampComboBox->addItem(wrestler.getName(), data);
        ui->tagChampComboBox1->addItem(wrestler.getName(), data);
        ui->tagChampComboBox2->addItem(wrestler.getName(), data);
        if (wrestler.getGender() == 1) {
            ui->womenChampComboBox->addItem(wrestler.getName(), data);
        }
    }

    // fills team combo box
    for (const team& t : m_teams) {
        QVariant data = QVariant::fromValue(const_cast<team*>(&t));
        ui->teamComboBox->addItem(t.getTeamName(), data);
    }

    // Set the current champions as the default selection if they exist
    // Women's Championship
    if (m_women.getChampion() != nullptr) { // Check if there are champions
        QString currentChampionName = m_women.getChampion()->getName(); // Use name
        int index = ui->womenChampComboBox->findText(currentChampionName); // Find based on name
        if (index != -1) {
            ui->womenChampComboBox->setCurrentIndex(index); // Set current champion as selected
        }
        else {
            qDebug() << "Women's Champion not found: " << currentChampionName;
        }
    }
    // World Championship
    if (!m_world.getChampions().isEmpty()) { // Check if there are champions
        QString currentChampionName = m_world.getChampion()->getName(); // Use name
        int index = ui->worldChampComboBox->findText(currentChampionName); // Find based on name

        if (index != -1) {
            ui->worldChampComboBox->setCurrentIndex(index); // Set current champion as selected
        }
        else{
            qDebug() << "World Champion not found: " << currentChampionName;
        }
    }
    // Shows both tag titles or neither
    if (m_tag.getChampions().size() > 1) { // Check if there are champions
        QString currentChampionName1 = m_tag.getChampions()[0]->getName();
        int index1 = ui->tagChampComboBox1->findText(currentChampionName1);
        if (index1 != -1) {
            ui->tagChampComboBox1->setCurrentIndex(index1);
        }

        QString currentChampionName2 = m_tag.getChampions()[1]->getName();
        int index2 = ui->tagChampComboBox2->findText(currentChampionName2);
        if (index2 != -1) {
            ui->tagChampComboBox2->setCurrentIndex(index2);
        }
    }
    else{
        ui->tagChampComboBox1->setCurrentIndex(0);  // "Vacant" option
        ui->tagChampComboBox2->setCurrentIndex(0);  // "Vacant" option
    }

    connect(ui->worldChampComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onWorldChampSelected);
    connect(ui->teamComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onTagChampSelected);
    connect(ui->tagChampComboBox1, &QComboBox::currentIndexChanged, this, &MainWindow::onManualTagChampsSelected);
    connect(ui->tagChampComboBox2, &QComboBox::currentIndexChanged, this, &MainWindow::onManualTagChampsSelected);
    connect(ui->womenChampComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onWomenChampSelected);
}
void MainWindow::onTagChampSelected(int index) {
    if (index < 0) return;

    QVariant data = ui->teamComboBox->itemData(index);
    team* selectedTeam = data.value<team*>();

    m_tag.setTagTeamChampions(selectedTeam);

}
void MainWindow::onManualTagChampsSelected() {
    int index1 = ui->tagChampComboBox1->currentIndex();
    int index2 = ui->tagChampComboBox2->currentIndex();

    if (index1 < 0 || index2 < 0 || index1 == index2) return; // Ensure valid selection

    QVariant data1 = ui->tagChampComboBox1->itemData(index1);
    QVariant data2 = ui->tagChampComboBox2->itemData(index2);

    Wrestler* wrestler1 = data1.value<Wrestler*>();
    Wrestler* wrestler2 = data2.value<Wrestler*>();

    if (!wrestler1 || !wrestler2) return;   // Ensure 2 are selected

    m_tag.setChampions( {wrestler1, wrestler2});
}
void MainWindow::onWorldChampSelected(int index) {
    if (index < 0) return; // No valid selection

    QVariant data = ui->worldChampComboBox->itemData(index);
    // Check if "Vacant" is selected
    if (data.isNull()) {
        m_world.setChampions({});  // Set champions to an empty list
        return;
    }

    Wrestler* selectedWrestler = data.value<Wrestler*>();

    m_world.setChampions({selectedWrestler});
}
void MainWindow::onWomenChampSelected(int index) {
    if (index < 0) return; // No valid selection

    QVariant data = ui->womenChampComboBox->itemData(index);
    // Check if "Vacant" is selected
    if (data.isNull()) {
        m_women.setChampions({});  // Set champions to an empty list
        return;
    }

    Wrestler* selectedWrestler = data.value<Wrestler*>();

    m_women.setChampions({selectedWrestler});
}
// radio buttons for whether to select tag champs by tag team or individuals
void MainWindow::on_teamNameRadio_toggled(bool checked)
{
    ui->teamComboBox->setEnabled(checked);  // Enable team selection
    ui->tagChampComboBox1->setEnabled(!checked);  // Disable individual selection
    ui->tagChampComboBox2->setEnabled(!checked);
}
void MainWindow::on_individualRadioButton_toggled(bool checked)
{
    ui->teamComboBox->setEnabled(!checked);  // Disable team selection
    ui->tagChampComboBox1->setEnabled(checked);  // enable individual selection
    ui->tagChampComboBox2->setEnabled(checked);
}

// tag teams
void MainWindow::populateTeamList()
{
    QWidget* container = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(container);
    container->setStyleSheet("background-color: #f0f0f0; color: black;");

    for (int i = 0; i < m_teams.size(); ++i) {
        team& team = m_teams[i];

        QHBoxLayout* hLayout = new QHBoxLayout;
        QLabel* teamNameLabel = new QLabel(team.getTeamName());

        teamNameLabel->setStyleSheet("color: black; font-size: 20px;");
        teamNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        // Display members
        QString membersList;
        for (Wrestler* wrestler : team.getMembers()) {
            if (wrestler) {
                if (!membersList.isEmpty()) {
                    membersList += ", ";
                }
                membersList += wrestler->getName();
            }
        }
        QLabel *membersLabel = new QLabel(membersList);

        // Edit Button
        QPushButton* editButton = new QPushButton("Edit");
        connect(editButton, &QPushButton::clicked, this, [this, &team, i]() {
            openEditTeamPage(m_teams[i]);
        });

        editButton->setStyleSheet(
            "background-color: #0078D7; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;");

        // Remove Button
        QPushButton* removeButton = new QPushButton("Remove");
        connect(removeButton, &QPushButton::clicked, this, [this, i]() {
            removeTeam(i);
        });
        removeButton->setStyleSheet(
            "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;");

        hLayout->addWidget(teamNameLabel);
        hLayout->addWidget(membersLabel);
        hLayout->addWidget(editButton);
        hLayout->addWidget(removeButton);

        layout->addLayout(hLayout);
    }

    container->setLayout(layout);
    ui->tagTeamScrollArea->setWidget(container);
    ui->tagTeamScrollArea->setWidgetResizable(true);
}
void MainWindow::openEditTeamPage(team& team)
{
    m_currentTeam = &team;
    // Set the team name in the input field
    ui->teamNameLineEdit->setText(team.getTeamName());

    // Clear the current wrestler ComboBox entries
    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->memberList->layout());
    if (!wrestlerLayout) {
        wrestlerLayout = new QGridLayout();
        ui->memberList->setLayout(wrestlerLayout);
    }

    // Remove existing widgets before repopulating
    while (wrestlerLayout->count() > 0) {
        QWidget* widget = wrestlerLayout->itemAt(0)->widget();
        wrestlerLayout->removeWidget(widget);
        delete widget;
    }

    int row = 0;
    for (Wrestler* wrestler : team.getMembers()) {
        QComboBox* wrestlerComboBox = new QComboBox(this);
        for (const Wrestler& w : m_playerRoster) {
            wrestlerComboBox->addItem(w.getName());
        }
        wrestlerComboBox->setCurrentText(wrestler->getName()); // Set current wrestler
        // Apply custom styling
        wrestlerComboBox->setStyleSheet(
            "QComboBox { background: #f0f0f0; border: 1px solid #888; padding: 4px; border-radius: 4px; color: black; }"
            "QComboBox::drop-down { width: 20px; border-left: 1px solid #888; background: #d3d3d3; }"
            "QComboBox::down-arrow { image: url(:/icons/down-arrow.png); width: 12px; height: 12px; }"
            "QComboBox QAbstractItemView { background: #f0f0f0; selection-background-color: #0078D7; color: black; border: 1px solid #888; }"
            );
        wrestlerComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        QPushButton* removeButton = new QPushButton("Remove", this);
        connect(removeButton, &QPushButton::clicked, this, [this, wrestlerComboBox]() {
            removeWrestlerFromTeam(wrestlerComboBox);
        });

        removeButton->setStyleSheet(
            "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;" );

        wrestlerLayout->addWidget(wrestlerComboBox, row, 0);
        wrestlerLayout->addWidget(removeButton, row, 1);
        row++;
    }
    // Show the team edit page
    ui->stackedWidget->setCurrentWidget(ui->editTeamPage);
    updateWrestlerTeamSelection();
}
void MainWindow::on_newTeamButton_clicked()
{
    // Create a new empty team
    m_currentTeam = new team();

    // Clear previous name
    ui->teamNameLineEdit->clear();

    // Clear previous combo boxes to select wrestlers
    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->memberList->layout());
    if (wrestlerLayout) {
        while (wrestlerLayout->count() > 0) {
            QWidget* widget = wrestlerLayout->itemAt(0)->widget();
            wrestlerLayout->removeWidget(widget);
            delete widget;
        }
    }

    // Disable save button initially
    ui->saveTeamButton->setEnabled(false);

    // Switch to team creation page
    ui->stackedWidget->setCurrentWidget(ui->editTeamPage);
    updateSaveTeamButton();
}
void MainWindow::removeTeam(int index) {
    // Confirm removal
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Remove Team",
        "Are you sure you want to remove this team?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_teams.removeAt(index);  // Remove the team from the list
        populateTeamList();  // Refresh the team list
    }
}
void MainWindow::on_addToTeamButton_clicked()
{
    // Ensure memberList has a valid layout (initialized only once)
    if (!ui->memberList->layout()) {
        ui->memberList->setLayout(new QGridLayout);  // Initialize layout if not done yet
    }

    // Create a new ComboBox for selecting a wrestler
    QComboBox* wrestlerComboBox = new QComboBox(this);

    // Get currently selected wrestlers to avoid duplicates
    QSet<QString> selectedWrestlers;
    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->memberList->layout());
    for (int i = 0; i < wrestlerLayout->count(); ++i) {
        QComboBox* existingCombo = qobject_cast<QComboBox*>(wrestlerLayout->itemAt(i)->widget());
        if (existingCombo) {
            selectedWrestlers.insert(existingCombo->currentText());
        }
    }

    // Populate with available wrestlers
    QStringList wrestlerNames;
    for (const Wrestler& wrestler : m_playerRoster) {
        if (!selectedWrestlers.contains(wrestler.getName())) {
            wrestlerNames.append(wrestler.getName());
        }
    }
    // Add check to ensure there's at least one wrestler
    if (wrestlerNames.isEmpty()) {
        return;  // Avoid adding a wrestler if there are no available wrestlers
    }

    wrestlerComboBox->addItems(wrestlerNames);
    wrestlerComboBox->setStyleSheet(
        "QComboBox { background: #f0f0f0; border: 1px solid #888; padding: 4px; border-radius: 4px; color: black; }"
        "QComboBox::drop-down { width: 20px; border-left: 1px solid #888; background: #d3d3d3; }"
        "QComboBox::down-arrow { image: url(:/icons/down-arrow.png); width: 12px; height: 12px; }"
        "QComboBox QAbstractItemView { background: #f0f0f0; selection-background-color: #0078D7; color: black; border: 1px solid #888; }"
        );
    wrestlerComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    wrestlerComboBox->addItems(wrestlerNames);
    connect(wrestlerComboBox, &QComboBox::currentTextChanged, this, [this]() {
        updateWrestlerTeamSelection();
    });

    int row = wrestlerLayout->rowCount();
    wrestlerLayout->addWidget(wrestlerComboBox, row, 0);
    // Create and configure the Remove button for the wrestler
    QPushButton* removeButton = new QPushButton("Remove", this);
    connect(removeButton, &QPushButton::clicked, this, [this, wrestlerComboBox]() {
        removeWrestlerFromTeam(wrestlerComboBox);  // Remove the selected wrestler ComboBox
    });

    removeButton->setStyleSheet(
        "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;"
        );

    // Add the Remove button next to the ComboBox in the same row
    wrestlerLayout->addWidget(removeButton, row, 1);

    // Ensure that the layout has been properly updated
    wrestlerLayout->update();  // Refresh layout after adding the widgets

    // Update the Save button status based on the number of wrestlers
    updateSaveTeamButton();
}
void MainWindow::removeWrestlerFromTeam(QComboBox* wrestlerComboBox) {
    if (!wrestlerComboBox) return;

    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->memberList->layout());
    if (!wrestlerLayout) return;

    int indexToRemove = -1;

    // Find the index of the ComboBox
    for (int i = 0; i < wrestlerLayout->count(); ++i) {
        QWidget* widget = wrestlerLayout->itemAt(i)->widget();
        if (widget == wrestlerComboBox) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        // Remove and delete the combo box
        QWidget* comboWidget = wrestlerLayout->itemAt(indexToRemove)->widget();
        wrestlerLayout->removeWidget(comboWidget);
        delete comboWidget;

        // Remove and delete the corresponding remove button
        QWidget* buttonWidget = wrestlerLayout->itemAt(indexToRemove)->widget();
        if (buttonWidget) {
            wrestlerLayout->removeWidget(buttonWidget);
            delete buttonWidget;
        }
    }

    updateSaveTeamButton();
}
void MainWindow::updateSaveTeamButton()
{
    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->memberList->layout());
    int wrestlerCount = 0;

    if (wrestlerLayout) {
        // Iterate through all items in the layout and count only the ComboBoxes
        for (int i = 0; i < wrestlerLayout->count(); ++i) {
            if (qobject_cast<QComboBox*>(wrestlerLayout->itemAt(i)->widget())) {
                wrestlerCount++;  // Count only the ComboBox widgets
            }
        }
    }

    // Enable the save button only if at least 2 wrestlers are added
    ui->saveTeamButton->setEnabled(wrestlerCount >= 2);
}
void MainWindow::updateWrestlerTeamSelection(){
    QSet<QString> selectedWrestlers;
    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->memberList->layout());

    // Collect selected wrestlers
    for (int i = 0; i < wrestlerLayout->count(); ++i) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(wrestlerLayout->itemAt(i)->widget());
        if (comboBox) {
            selectedWrestlers.insert(comboBox->currentText());
        }
    }

    // Update each combo box
    for (int i = 0; i < wrestlerLayout->count(); ++i) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(wrestlerLayout->itemAt(i)->widget());
        if (comboBox) {
            QString currentSelection = comboBox->currentText();

            // Block signals to prevent crashes
            comboBox->blockSignals(true);

            // Clear and repopulate the ComboBox
            comboBox->clear();
            QStringList wrestlerNames;
            for (const Wrestler& wrestler : m_playerRoster) {
                if (!selectedWrestlers.contains(wrestler.getName()) || wrestler.getName() == currentSelection) {
                    wrestlerNames.append(wrestler.getName());
                }
            }

            comboBox->addItems(wrestlerNames);
            comboBox->setCurrentText(currentSelection);

            // Re-enable signals
            comboBox->blockSignals(false);
        }
    }
}
void MainWindow::on_saveTeamButton_clicked()
{
    if (!m_currentTeam) return;

    // Update team name
    m_currentTeam->setTeamName(ui->teamNameLineEdit->text().trimmed());

    if (m_currentTeam->getTeamName().isEmpty()) {
        QMessageBox::warning(this, "Invalid Team", "Please enter a valid team name.");
        return;
    }

    // Clear existing members and update with selected wrestlers
    m_currentTeam->clearWrestlers();

    QGridLayout* wrestlerLayout = qobject_cast<QGridLayout*>(ui->memberList->layout());
    if (wrestlerLayout) {
        for (int i = 0; i < wrestlerLayout->count(); ++i) {
            QComboBox* comboBox = qobject_cast<QComboBox*>(wrestlerLayout->itemAt(i)->widget());
            if (comboBox) {
                QString selectedWrestler = comboBox->currentText();
                for (Wrestler &w : m_playerRoster) {
                    if (w.getName() == selectedWrestler) {
                        m_currentTeam->addMember(&w);
                        break;
                    }
                }
            }
        }
    }

    // Ensure at least 2 wrestlers are in the team before saving
    if (m_currentTeam->getMembers().size() < 2) {
        QMessageBox::warning(this, "Invalid Team", "A team must have at least two wrestlers.");
        return;
    }

    // Check if the team is already in m_teams
    bool isExistingTeam = false;
    for (int i = 0; i < m_teams.size(); ++i) {
        if (m_teams[i].getTeamName() == m_currentTeam->getTeamName()) {
            m_teams[i] = *m_currentTeam; // Update existing team
            isExistingTeam = true;
            break;
        }
    }

    // If it's a new team, add it to m_teams
    if (!isExistingTeam) {
        m_teams.append(*m_currentTeam);
    }
    // Refresh team list and go back to team overview page
    populateTeamList();
    ui->stackedWidget->setCurrentWidget(ui->tagTeamPage);
}






