#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "wrestler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("PWGM");

    ui->wrestlerImage->installEventFilter(this);    // for changing size of wrestler img


    dataManager = new GameDataManager();
    dataManager->openDatabase();
    dataManager->initializeDatabase();

    loadMaterialFont();

    // Ensures the initial page is the landing page
    ui->stackedWidget->setCurrentWidget(ui->LandingPage);

    // Hide navigation buttons that show up on all pages except the game select screen
    ui->RosterTab->hide();
    ui->DashboardTab->hide();
    ui->PromotionTab->hide();
    ui->SettingsTab->hide();


    ui->sortByAttributesCB->addItems({"Name", "Popularity", "Health", "Age",
                                    "Salary", "Role", "Gender", "Charisma", "Stamina",});
    m_textColor = Qt::black;
    m_backgroundColor = Qt::white;

    // Options for how to select tag team champs, not yet completed
    ui->teamNameRadio->hide();
    ui->individualRadioButton->hide();
    ui->teamComboBox->hide();
    ui->customRoster->hide();
    ui->ppvLabel1->hide();

    ui->skip26WeeksButton->hide();

    // Apply style to combo boxes
    ui->sortByAttributesCB->setStyleSheet(m_comboBoxStyle);
    ui->matchTypeComboBox->setStyleSheet(m_comboBoxStyle);
    ui->winnerComboBox->setStyleSheet(m_comboBoxStyle);
    ui->worldChampComboBox->setStyleSheet(m_comboBoxStyle);
    ui->tagChampComboBox1->setStyleSheet(m_comboBoxStyle);
    ui->tagChampComboBox2->setStyleSheet(m_comboBoxStyle);
    ui->womenChampComboBox->setStyleSheet(m_comboBoxStyle);
    ui->feudWrestler1ComboBox->setStyleSheet(m_comboBoxStyle);
    ui->feudWrestler2ComboBox->setStyleSheet(m_comboBoxStyle);
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
void MainWindow::on_finalizeBooking_clicked(){
    finalizeBooking();
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
    // Shows player roster
    ui->stackedWidget->setCurrentWidget(ui->viewRoster);
    populateWrestlerList(m_playerRoster);

    // ensures the roster the player will be looking at would be own
    m_currentRoster = &m_playerRoster;
    m_currentAffiliation = 1;

    updateRosterLabel();

    // ensures the edit button is the one that is displayed
    ui->saveNameButton->hide();
    ui->editNameButton->show();
}
void MainWindow::on_RivalPromotionTab_clicked()
{
    // ensures user cannot edit the names of other promotions' wrestlers
    ui->saveNameButton->hide();
    ui->editNameButton->setEnabled(false);
    ui->editNameButton->clearFocus();

    ui->stackedWidget->setCurrentWidget(ui->viewRoster);
    populateWrestlerList(m_cpuRoster);

    //ensures the roster the player will be viewing will be cpu's
    m_currentRoster = &m_cpuRoster;
    m_currentAffiliation = 2;

    updateRosterLabel();
}
void MainWindow::on_FreeAgentTab_clicked()
{
    // ensures user cannot edit the names of unsigned wrestlers
    ui->saveNameButton->hide();
    ui->editNameButton->setEnabled(false);
    ui->editNameButton->clearFocus();

    ui->stackedWidget->setCurrentWidget(ui->viewRoster);
    populateWrestlerList(m_freeAgents);

    //ensures the roster the player will be viewing will be free agents
    m_currentRoster = &m_freeAgents;
    m_currentAffiliation = 0;

    updateRosterLabel();
}
void MainWindow::on_rosterBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Roster_Page);
}
void MainWindow::on_backFromWrestler_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->viewRoster);
    populateWrestlerList(*m_currentRoster);
    // ensures the edit button is the one that is displayed
    ui->saveNameButton->hide();
    ui->editNameButton->show();
}
void MainWindow::on_backToLanding_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->LandingPage);
}
void MainWindow::on_InjuredTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->InjuredList);
    populateInjuredWrestlersList(m_playerRoster);

}
void MainWindow::on_InjuredBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Roster_Page);
}
void MainWindow::on_ChampionTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->ChampionshipPage);
    setUpChampionSelection();
}
void MainWindow::on_champBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Roster_Page);
}
void MainWindow::on_TeamsTab_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->tagTeamPage);
    populateTeamList();
}
void MainWindow::on_teamsBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Roster_Page);
}
void MainWindow::on_FeudsTab_clicked()
{
    populateRivalryList();
}
void MainWindow::on_rivalryBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Roster_Page);
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

    for (Wrestler* w : m_playerRoster ){
        if (w->getInjury() <= 0){
            w->recoverHealth(10);
        }
        else{
            w->recoverInjury();
        }
    }

    // Process player contracts (by match)
    for (int i = m_playerRoster.size() - 1; i >= 0; --i) {
        Wrestler* w = m_playerRoster[i];

        if (w->getTotalMatchesRemaining() <= 0) {  // contract expired
            m_playerRoster.removeAt(i);
            w->setAffiliation(0);  // free agent
            m_freeAgents.append(w);
        }
    }

    // process cpu contracts (by weeks)


    updateCpuRosterWeekly();

    // show navigation buttons that show up on all pages except few
    ui->RosterTab->show();
    ui->DashboardTab->show();
    ui->PromotionTab->show();
    ui->SettingsTab->show();
}
void MainWindow::on_homeButton_clicked()
{
    clearData();
    // hide navigation buttons that show up on all pages except few
    ui->RosterTab->hide();
    ui->DashboardTab->hide();
    ui->PromotionTab->hide();
    ui->SettingsTab->hide();
}

// Skips 26 weeks; used for debugging

// Load the Material Symbols font
void MainWindow::loadMaterialFont()
{
    // Ensure a known default font is set before applying Material Symbols
    QFont defaultFont("Arial"); // Choose a widely available font like Arial
    defaultFont.setPointSize(10); // Set a reasonable default size
    qApp->setFont(defaultFont); // Apply globally

    // Load Material Symbols font
    QString fontPath = ":/fonts/MaterialSymbolsRounded_36pt-Regular.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);

    if (fontId == -1) {
        qWarning() << "Failed to load Material Symbols font!";
        //return;
    }


    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.isEmpty()) {
        m_materialFont = QFont(fontFamilies.first());
        m_materialFont.setPointSize(36);  // Adjust size as needed
    }
}

// Loading and creating roster
void MainWindow::on_StartNew_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->newFilePage);
}
void MainWindow::on_defaultRoster_clicked()
{
    QList<Wrestler*> allWrestlers = dataManager->loadDefaultRoster();

    if (allWrestlers.size() <= 1) {
        QMessageBox::warning(this, "Incomplete Data",
                             "Too few entries in file to be used");
        return;  // Stop the game loading process
    }

    setRosters(allWrestlers);

    newGameSetup();
}
void MainWindow::on_customRoster_clicked()
{
    // Open a file dialog to select the file
    QString filePath = QFileDialog::getOpenFileName(this, "Open Roster File", "", "Text Files (*.txt);;All Files (*)");

    if (filePath.isEmpty()) {
        return;  // If no file is selected, return early
    }

    if (m_playerRoster.size() < 10){
        QMessageBox::information(this, "Information", "There was not enough valid rows that can be loaded.");
        return;
    }
    newGameSetup();
}
void MainWindow::on_randomRoster_clicked() {
    srand(static_cast<unsigned int>(time(0)));

    // Clear existing rosters
    for (Wrestler* w : m_playerRoster) delete w;
    for (Wrestler* w : m_cpuRoster) delete w;
    for (Wrestler* w : m_freeAgents) delete w;

    m_playerRoster.clear();
    m_cpuRoster.clear();
    m_freeAgents.clear();

    m_lastUsedID = 1;

    // --- Preload default faces once ---
    QStringList menFaces = loadFaceFiles(false);
    QStringList womenFaces = loadFaceFiles(true);

    auto getRandomFace = [&](bool isFemale) {
        return isFemale ? randomFace(womenFaces) : randomFace(menFaces);
    };

    // --- Player roster ---
    for (int i = 0; i < 20; ++i) {
        Wrestler* w = new Wrestler(m_lastUsedID++);
        w->setAffiliation(1);

        bool isFemale = w->isFemale();
        w->setFacePath(getRandomFace(isFemale));

        m_playerRoster.append(w);
    }

    // --- CPU roster ---
    for (int i = 0; i < 20; ++i) {
        Wrestler* w = new Wrestler(m_lastUsedID++);
        w->setAffiliation(2);

        bool isFemale = w->isFemale();
        w->setFacePath(getRandomFace(isFemale));

        m_cpuRoster.append(w);
    }

    // --- Free agents ---
    for (int i = 0; i < 30; ++i) {
        Wrestler* w = new Wrestler(m_lastUsedID++);
        w->setAffiliation(0);
        w->clearContractSegments();

        bool isFemale = w->isFemale();
        w->setFacePath(getRandomFace(isFemale));

        m_freeAgents.append(w);
    }

    newGameSetup();
}
void MainWindow::on_LoadGame_clicked()
{
    // Load all wrestlers
    QList<Wrestler*> allWrestlers = dataManager->loadWrestlers();

    if (allWrestlers.size() <= 5) {
        QMessageBox::warning(this, "Incomplete Data",
                             "Too few entries in file to be used");
        return;  // Stop the game loading process
    }

    // Clear existing rosters before refilling
    m_playerRoster.clear();
    m_freeAgents.clear();
    m_cpuRoster.clear();

    setRosters(allWrestlers);

    // Build ID -> pointer map
    QMap<int, Wrestler*> wrestlerMap;
    for (Wrestler* w : allWrestlers) wrestlerMap[w->getID()] = w;


    // Load championships, then store them in m_world, m_tag, and m_women
    QList<championship*> loadedChamps;
    dataManager->loadChampionships(loadedChamps, wrestlerMap);// Check if the list is not empty and has the expected number of championships

    if (loadedChamps.size() >= 3) {
        m_world = *loadedChamps[0];
        m_tag = *loadedChamps[1];
        m_women = *loadedChamps[2];
    }
    // Load teams and store them in m_teams
    dataManager->loadTeams(m_teams,wrestlerMap);
    // Load rivalries
    dataManager->loadRivalries(m_rivalries, wrestlerMap);
    // Load game info and store it in m_money, m_fans, m_year, m_currentWeek, etc.
    dataManager->loadGameInfo(m_money, m_fans, m_year, m_currentWeek, m_moneyHistory, m_fanHistory, m_darkMode);
    // Load the current show and store it in m_currentShow
    dataManager->loadShow(m_currentShow, wrestlerMap);

    ui->stackedWidget->setCurrentWidget(ui->Dashboard_Page);
    ui->RosterTab->show();
    ui->DashboardTab->show();
    ui->PromotionTab->show();
    ui->SettingsTab->show();

    if (m_darkMode) {
        ui->darkModeCheckBox->setChecked(m_darkMode);
        m_textColor = QColor("#F5F5F5");
        m_backgroundColor = QColor("#1E1E1E");
        m_darkMode = 1; // ensures dark mode is on

    }
    applyTheme();

    updateDashboardLabels();
}
void MainWindow::on_userSave_clicked()
{
    // save game data into sqlite using the GameDataManager
    dataManager->saveWrestlers(m_playerRoster, m_cpuRoster, m_freeAgents);          // save wrestlers from m_playerRoster
    dataManager->saveChampionships(m_world, m_tag, m_women); // save championships
    dataManager->saveTeams(m_teams);                      // save teams
    dataManager->saveRivalries(m_rivalries);
    dataManager->saveGameInfo(m_money, m_fans, m_year, m_currentWeek,
                              m_moneyHistory, m_fanHistory, m_darkMode); // Load game-specific info
    dataManager->saveShow(m_currentShow);                 // save current show data

    // Set the last used ID (assuming it is saved in the database or calculated from the loaded data)
    m_lastUsedID = m_playerRoster.size() + 1;  // or another approach to set the last ID
}
void MainWindow::setRosters(QList<Wrestler*> wrestlers){
    // Sort wrestlers into rosters based on affiliation
    for (Wrestler* w : wrestlers) {
        int aff = w->getAffiliation();

        if (aff == 1) {                // Player promotion
            m_playerRoster.append(w);
        }
        else if (aff == 2) {          // cpu pool
            m_cpuRoster.append(w);
        }
        else {                         // free agent pool
            m_freeAgents.append(w);
            w->clearContractSegments(); // ensures wrestler has no contract signed
        }
    }

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

void MainWindow::makeCharts(const QList<int>& values, QWidget* chartWidget) {
    if (QLayout* layout = chartWidget->layout()) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (QWidget* w = item->widget()) {
                delete w; // deletes QChartView
            }
            delete item;
        }
    }

    QLineSeries *series = new QLineSeries();

    // Compute actual weeks stored in the values list
    QList<int> weeks;
    for (int i = 0; i < values.size(); ++i) {
        weeks.append(m_currentWeek - (values.size() - 1) + i);
    }

    // Add data points using actual weeks
    for (int i = 0; i < values.size(); ++i) {
        series->append(weeks[i], values[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Change over 5 Weeks");

    // Configure X-Axis (Weeks)
    QValueAxis *axisX = new QValueAxis();
    if (!weeks.isEmpty()) {
        axisX->setRange(weeks.first(), weeks.last());  // Ensure continuous range
    }
    axisX->setTickCount(values.size());
    axisX->setTitleText("Weeks");
    axisX->setLabelFormat("%d");  // Ensure integer labels
    axisX->setLabelsBrush(QBrush(m_textColor));
    axisX->setTitleBrush(QBrush(m_textColor));
    axisX->setGridLineColor(m_textColor);
    axisX->setLinePenColor(m_textColor);

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configure Y-Axis (Fans/Money)
    QValueAxis *axisY = new QValueAxis();
    int maxValue = values.isEmpty() ? 1 : std::max(1, *std::max_element(values.begin(), values.end()));
    axisY->setRange(0, 1.1 * maxValue);
    axisY->setTitleText(values == m_fanHistory ? "Fans" : "Money");
    axisY->setLabelsBrush(QBrush(m_textColor));
    axisY->setTitleBrush(QBrush(m_textColor));
    axisY->setGridLineColor(m_textColor);
    axisY->setLinePenColor(m_textColor);

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


// Calculates and shows results of a show
void MainWindow::finalizeBooking(){
    // Set ratings for each match and update championships if necessary
    for ( match &m : m_currentShow.getMatchesEdit()) {
        m.calcMatchRating(m.getParticipants());
        // Apply title change for each championship if applicable
        if (m.isChampionship()) {
            m.applyTitleChange(&m_world);  // For world championship
            m.applyTitleChange(&m_tag);    // For tag team championship
            m.applyTitleChange(&m_women);  // For women's championship
        }
        // Process health loss and injuries for each wrestler in the match
        for (Wrestler* wrestler : m.getParticipants()) {
            if (wrestler) {
                m.calculateHealthLoss(wrestler); // This should handle health updates
                m.determineInjuryDuration(wrestler); // This should handle injury updates
            }
        }
    }

    // Calculates values for the show
    m_currentShow.calculateShowRating();
    m_currentShow.calculateCosts();
    m_currentShow.calculateFanImpact(m_fans);
    m_currentShow.calculateShowRevenue(m_fans);

    // Updates contract segments
    m_currentShow.advanceContract();

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
void MainWindow::populateResultsList() {
    QList<match>& matches = m_currentShow.getMatchesEdit();

    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    ui->weekLabel->setText("Week " + QString::number(m_currentWeek));

    // Path to championship title image (ensure this path is correct)
    QPixmap titlePixmap(":/icons/myBasicTitle.png"); // Championship title image

    if (titlePixmap.isNull()) {
        qWarning() << "Championship title image not found!";
    }

    for (match& m : matches) {
        QVBoxLayout *matchLayout = new QVBoxLayout;

        // Match Type
        QLabel *matchTypeLabel = new QLabel(m.getMatchType());
        matchTypeLabel->setStyleSheet(QString("font-weight: bold; color: %1; font-size: 24px;")
                                          .arg(m_textColor.name()));
        matchLayout->addWidget(matchTypeLabel);

        // Get participants and determine teams if it's a tag match
        QList<Wrestler*> participants = m.getParticipants();
        bool isTeamMatch = m.isTeam();

        QString participantText;

        // If it's a tag match, we format participants in teams
        if (isTeamMatch) {
            int teamSize = std::ceil(participants.size() / 2.0);
            QList<Wrestler*> team1 = participants.mid(0, teamSize);
            QList<Wrestler*> team2 = participants.mid(teamSize, participants.size() - teamSize);

            // Display team participants in a compact format
            QString team1Text, team2Text;
            for (Wrestler* wrestler : team1) {
                if (!team1Text.isEmpty()) team1Text += ", ";
                team1Text += wrestler->getName();
            }
            for (Wrestler* wrestler : team2) {
                if (!team2Text.isEmpty()) team2Text += ", ";
                team2Text += wrestler->getName();
            }

            QLabel *team1Label = new QLabel(team1Text);
            QLabel *team2Label = new QLabel(team2Text);
            team1Label->setStyleSheet(QString("color: %1; font-size: 20px;")
                                          .arg(m_textColor.name()));
            team2Label->setStyleSheet(QString("color: %1; font-size: 20px;")
                                          .arg(m_textColor.name()));

            matchLayout->addWidget(team1Label);

            QLabel *spacer = new QLabel(" ");
            matchLayout->addWidget(spacer);
            matchLayout->addWidget(team2Label);

            // Determine the winning team
            bool firstTeamWins = team1.contains(m.getWinner());
            QList<Wrestler*> winningTeam = firstTeamWins ? team1 : team2;

            // Winner Label for team matches
            QString winnerText = "<b>Winning Team:</b> ";
            for (Wrestler* wrestler : winningTeam) {
                if (!winnerText.endsWith(": ")) winnerText += ", ";
                winnerText += wrestler->getName();
            }
            QLabel *winnerLabel = new QLabel(winnerText);
            winnerLabel->setStyleSheet(QString("color: %1; font-size: 20px;")
                                           .arg(m_textColor.name()));
            matchLayout->addWidget(winnerLabel);
        } else {
            // display the winner in a default way
            QStringList participantNames;
            for (Wrestler* wrestler : participants) {
                participantNames.append(wrestler->getName());
            }
            participantText = participantNames.join(", ");

            QLabel *singleMatchLabel = new QLabel(participantText);
            singleMatchLabel->setStyleSheet(QString("color: %1; font-size: 20px;")
                                                .arg(m_textColor.name()));
            matchLayout->addWidget(singleMatchLabel);

            // Winner Label for single matches
            QLabel *winnerLabel = new QLabel("<b>Winner:</b> " + m.getWinner()->getName());
            winnerLabel->setStyleSheet(QString("color: %1; font-size: 20px;")
                                           .arg(m_textColor.name()));
            matchLayout->addWidget(winnerLabel);
        }

        // Display championship title for title matches
        if (m.isChampionship()) {
            QLabel *champNewLabel = new QLabel;
            champNewLabel->setPixmap(titlePixmap.scaled(30, 30, Qt::KeepAspectRatio));
            matchLayout->addWidget(champNewLabel);
        }

        // Rating Label (with star symbol)
        QLabel *ratingLabel = new QLabel(QString("<span style='color: #cc9900; font-size: 20px;'>\u2605</span> %1")
                                             .arg(QString::number(m.getRating(), 'f', 1)));
        ratingLabel->setStyleSheet(QString("color: %1")
                                       .arg(m_textColor.name()));
        matchLayout->addWidget(ratingLabel);

        m.applyAttributeGains();    // See if any stats change
        // Display attribute changes for all participants
        for (Wrestler* wrestler : m.getParticipants()) {
            if (m.getAttributeChanges().contains(wrestler)) {
                QMap<QString, int> changes = m.getAttributeChanges()[wrestler];
                QString changeText = QString("%1: ").arg(wrestler->getName());

                // Iterate through each attribute change and append to the changeText
                for (auto it = changes.begin(); it != changes.end(); ++it) {
                    QString label = it.key();
                    int change = it.value();

                    // Append each attribute change to the text
                    changeText += QString("%1 +%2, ").arg(label).arg(change);
                }

                // Remove the trailing comma and space
                if (changeText.endsWith(", ")) {
                    changeText.chop(2);
                }

                // Create a QLabel to display the changes
                QLabel *changeLabel = new QLabel(changeText);
                changeLabel->setStyleSheet(QString("color: %1; font-size: 16px;").arg(m_textColor.name()));
                matchLayout->addWidget(changeLabel);
            }
        }

        // Shows who got injured in a match
        bool hasInjuries = false;
        for (Wrestler* w : participants) {
            if (w->getInjury() > 0 ) {
                hasInjuries = true;
                break;
            }
            }
        if (hasInjuries) {
            QLabel *injuryHeader = new QLabel("<b>Injuries:</b>");
            matchLayout->addWidget(injuryHeader);

            for (Wrestler* w : participants) {
                if (w->getInjury() > 0) {
                    QHBoxLayout *injuredLayout = new QHBoxLayout;

                    QLabel *iconLabel = new QLabel;
                    iconLabel->setPixmap(QPixmap(":/icons/healing_red.png").scaled(20, 20, Qt::KeepAspectRatio));

                    QLabel *textLabel = new QLabel(
                        QString("%1 (Out %2 weeks)").arg(w->getName()).arg(w->getInjury())
                        );
                    textLabel->setStyleSheet(QString("color: %1; font-size: 20px;").arg(m_textColor.name()));

                    injuredLayout->addWidget(iconLabel);
                    injuredLayout->addWidget(textLabel);
                    // expanding spacer to push labels to the left
                    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
                    injuredLayout->addSpacerItem(spacer);

                    matchLayout->addLayout(injuredLayout);
                }
            }
        }
        // Add a visual divider (horizontal line)
        QFrame *line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setStyleSheet(QString("background-color: %1; height: 2px;").arg(m_textColor.name()));
        matchLayout->addWidget(line);

        // Add match layout to the main layout
        layout->addLayout(matchLayout);
    }

    container->setLayout(layout);
    ui->matchResults->setWidget(container);  // Assign to the results scroll area
    ui->matchResults->setWidgetResizable(true);

    // Hide navigation buttons that show up on all pages except the game select screen
    ui->RosterTab->hide();
    ui->DashboardTab->hide();
    ui->PromotionTab->hide();
    ui->SettingsTab->hide();
}
void MainWindow::updateDashboardLabels(){
    ui->fansDisplay->setText("Fans: " + QString::number(m_fans));
    ui->moneyDisplay->setText("Money: $" + QString::number(m_money));
    ui->WeekDisplay->setText("Week: " + QString::number(m_currentWeek));
    ui->yearDisplay->setText("Year: " + QString::number(m_year));
}

// For displaying and editing wrestlers on roster
void MainWindow::populateWrestlerList(QList<Wrestler*> &wrestlers) {
    QWidget* previousContainer = ui->scrollArea->widget();
    if (previousContainer) {
        delete previousContainer;
    }


    QWidget *container = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(container);

    QGridLayout *grid = new QGridLayout;
    QString legendStyle = QString("font-weight: bold; text-decoration: underline; color: %1; font-size: 18px;")
                              .arg(m_textColor.name());

    QStringList headers = {"Popularity", "Gender", "Name", "Role", "Age", "Health"};
    for (int col = 0; col < headers.size(); ++col) {
        QLabel *label = new QLabel(headers[col]);
        label->setStyleSheet(legendStyle);
        label->setAlignment(Qt::AlignCenter);
        grid->addWidget(label, 0, col);
    }

    int row = 1; // start data rows after legend

    for (Wrestler* wrestler : wrestlers) {
        // Popularity
        QLabel *popularityValue = new QLabel(QString::number(wrestler->getPopularity()));
        popularityValue->setStyleSheet(QString("color: %1; font-size: 16px;").arg(m_textColor.name()));
        popularityValue->setAlignment(Qt::AlignCenter);
        grid->addWidget(popularityValue, row, 0);

        // Gender symbol
        QString genderSymbol = wrestler->isFemale() ? QStringLiteral(u"\u2640") : QStringLiteral(u"\u2642");
        QFont genderFont;
        genderFont.setPointSize(20);
        genderFont.setBold(true);     // Force bold and increase size so symbols are more visible

        QLabel *genderValue = new QLabel(genderSymbol);
        genderValue->setFont(genderFont);
        genderValue->setStyleSheet(QString("color: %1;").arg(m_textColor.name()));
        genderValue->setAlignment(Qt::AlignCenter);
        grid->addWidget(genderValue, row, 1);

        // Name as button
        QPushButton *nameButton = new QPushButton(wrestler->getName());
        nameButton->setCursor(Qt::PointingHandCursor);
        if (wrestler->getInjury() > 0){
            nameButton->setIcon(injuredIconRed); // Set the injury icon
            nameButton->setIconSize(QSize(20, 20)); // Adjust icon size as needed
        }
        QString buttonStyle = m_darkMode
                                  ? "QPushButton { border: none; background: transparent; text-align: left; color: #A7C7FF; font-size: 16px; }"
                                  : "QPushButton { border: none; background: transparent; text-align: left; color: blue; font-size: 16px; }";
        nameButton->setStyleSheet(buttonStyle);
        connect(nameButton, &QPushButton::clicked, this, [this, wrestler]() {
            ui->stackedWidget->setCurrentWidget(ui->wrestlerStats);
            updateWrestlerDetails(wrestler);
        });
        grid->addWidget(nameButton, row, 2);

        // Role
        QLabel *roleValue = new QLabel;
        switch (wrestler->getRole()) {
        case 1: roleValue->setText("Villain"); break;
        case 2: roleValue->setText("Hero"); break;
        default: roleValue->setText("Neutral"); break;
        }
        roleValue->setStyleSheet(QString("color: %1; font-size: 16px;").arg(m_textColor.name()));
        roleValue->setAlignment(Qt::AlignCenter);
        grid->addWidget(roleValue, row, 3);

        // Age
        QLabel *ageValue = new QLabel(QString::number(wrestler->getAge()));
        ageValue->setStyleSheet(QString("color: %1; font-size: 16px;").arg(m_textColor.name()));
        ageValue->setAlignment(Qt::AlignCenter);
        grid->addWidget(ageValue, row, 4);

        // Health
        QLabel *healthValue = new QLabel(QString::number(wrestler->getHealth()));
        healthValue->setStyleSheet(QString("color: %1; font-size: 16px;").arg(m_textColor.name()));
        healthValue->setAlignment(Qt::AlignCenter);
        grid->addWidget(healthValue, row, 5);

        ++row;
    }

    mainLayout->addLayout(grid);
    container->setLayout(mainLayout);
    ui->scrollArea->setWidget(container);
    ui->scrollArea->setWidgetResizable(true);
}
void MainWindow::updateRosterLabel(){
    if (*m_currentRoster == m_playerRoster){
        ui->rosterLabel->setText("Your Roster");
    }
    else if (*m_currentRoster == m_cpuRoster){
        ui->rosterLabel->setText("Rival's Roster");
    }
    else if (*m_currentRoster == m_freeAgents){
        ui->rosterLabel->setText("Free Agents");
    }
}
void MainWindow::updateWrestlerDetails( Wrestler* wrestler) {

    if (wrestler == nullptr) {
        qDebug() << "Error: Wrestler pointer is null!";
        return;
    }

    Wrestler* m_currentWrestler = nullptr;


    // Load wrestler face
    QString facePath = wrestler->getFacePath();
    if (!facePath.isEmpty()) {
        QPixmap pix(facePath);   // Load QPixmap from resource
        if (!pix.isNull()) {
            m_currentFace = pix; // store it for resizing
            updateWrestlerImage(); // scale and display
        } else {
            qDebug() << "Failed to load face:" << facePath;
            ui->wrestlerImage->clear();
        }
    } else {
        ui->wrestlerImage->clear();
    }

    ui->wrestlerNamelineEdit->setText(wrestler->getName());
    ui->wrestlerNamelineEdit->setReadOnly(true);    // name cannot be edited until user chooses to

    // Set font size and alignment for the name
    QFont nameFont;
    nameFont.setPointSize(24);
    ui->wrestlerNamelineEdit->setFont(nameFont);
    ui->wrestlerNamelineEdit->setAlignment(Qt::AlignCenter);

    ui->wrestlerNamelineEdit->setStyleSheet(QString("color: %1;")
                                      .arg(m_textColor.name()));

    disconnect(ui->wrestlerNamelineEdit, nullptr, nullptr, nullptr); // disconnect all slots

    if (wrestler->getAffiliation() == 1) {
        connect(ui->wrestlerNamelineEdit, &QLineEdit::editingFinished, this, [this, wrestler]() {
            wrestler->setName(ui->wrestlerNamelineEdit->text());
            ui->wrestlerNamelineEdit->setReadOnly(true);
            ui->editNameButton->setText("Edit Name");
        });
        ui->editNameButton->setEnabled(true);
    } else {
        ui->editNameButton->setEnabled(false);
    }


    ui->ageLabel->setText("Age: " + QString::number(wrestler->getAge()));

    ui->powerhouseLabel->setText("Powerhouse: " + QString::number(wrestler->getPowerhouse()));
    ui->brawlerLabel->setText("Brawler: " + QString::number(wrestler->getBrawler()));
    ui->highFlyerLabel->setText("High Flyer: " + QString::number(wrestler->getHighFlyer()));
    ui->technicianLabel->setText("Technician: " + QString::number(wrestler->getTechnician()));
    ui->mmaLabel->setText("MMA: " + QString::number(wrestler->getMMA()));

    ui->populatiryLabel->setText("Popularity: " + QString::number(wrestler->getPopularity()));
    ui->charismaLabel->setText("Charisma: " + QString::number(wrestler->getCharisma()));
    ui->staminaLabel->setText("Stamina: " + QString::number(wrestler->getStamina()));
    ui->healthLabel->setText("Health: " + QString::number(wrestler->getHealth()));

    ui->salaryLabel->setText("Salary: $" + QString::number(wrestler->getCurrentSalary()));

    ui->matchesRemainingLabel->setText("Matches Remaining: " +QString::number(wrestler->getTotalMatchesRemaining()));

    QString roleText;
    switch (wrestler->getRole()) {
    case 1: roleText = "Villain"; break;
    case 2: roleText = "Hero"; break;
    default: roleText = "Neutral"; break;
    }
    ui->roleLabel->setText("Role: " + roleText);

    // Set genderLabel based on wrestler.gender (0 = M, 1 = F)
    QString genderText = wrestler->isFemale() ? "F" : "M";
    ui->genderLabel->setText("Gender: " + genderText);

    if (wrestler->getInjury() <= 0) {
        ui->injuredLabel->hide();
    }
    else{
        //ui->injuredLabel->setFont(m_materialFont);
        ui->injuredLabel->show();
        ui->injuredLabel->setStyleSheet("background-color: rgb(200, 0, 0); "
                                        "color: white;");
        // Sets everything but hurt icon to different font, %2 is placeholder for getInjury
        QString injured = QString("<span style='font-family: Material Symbols Rounded 36pt; font-size: 18px; line-height: 1;'>%1</span> "
                                  "<span style='font-family: Arial; font-size: 20px;'>Injured %2 weeks</span>")
                              .arg(injuredIcon)
                              .arg(wrestler->getInjury());
        ui->injuredLabel->setText(injured);
        ui->injuredLabel->adjustSize(); // Supposed to remove the weird red empty space above the text
    }

    QString grade;
    QString color;

    int potential = wrestler->getPotential();

    // Determine grade and color
    if (potential >= 475) {
        grade = "A+";
        color = "#006400"; // Dark Green
    } else if (potential >= 450) {
        grade = "A";
        color = "#006400";
    } else if (potential >= 400) {
        grade = "B+";
        color = "#32CD32"; // Light Green
    } else if (potential >= 375) {
        grade = "B";
        color = "#32CD32";
    } else if (potential >= 325) {
        grade = "C+";
        color = "#FFD700"; // Gold
    } else if (potential >= 300) {
        grade = "C";
        color = "#FFD700";
    } else if (potential >= 250) {
        grade = "D+";
        color = "#FFA500"; // Orange
    } else if (potential >= 225) {
        grade = "D";
        color = "#FFA500";
    } else if (potential >= 125) {
        grade = "E";
        color = "#FF0000"; // Red
    } else {
        grade = "F";
        color = "#8B0000"; // Dark Red
    }

    // Set the plain text and stylesheet color
    ui->potentialValueLabel->setText(grade);
    ui->potentialValueLabel->setStyleSheet(QString(
                                               "QLabel { color: %1; font-weight: bold; font-size: 58pt; }"
                                               ).arg(color));

    // if wrestler is scouted
    if (wrestler->getAffiliation() == -1) {
        // Scouted wrestler path
        ui->signButton->show();
        ui->declineSignButton->show();

        ui->saveNameButton->hide();

        ui->extensionWidget->hide();
        ui->extensionSalaryLabel->hide();
        ui->salaryLabel->hide();

        ui->signSalaryLabel->show();
        ui->signSalaryLabel->setText("Sign per Match: $" + QString::number(wrestler->calcSalary()));

        ui->matchesRemainingLabel->hide();

        disconnect(ui->signButton, nullptr, nullptr, nullptr);
        connect(ui->signButton, &QPushButton::clicked, this, &MainWindow::signNewRecruit);
        connect(ui->declineSignButton, &QPushButton::clicked, this, &MainWindow::declineSign);
    }
    // if wrestlers is a free agent
    else if (wrestler->getAffiliation() == 0 || wrestler->getTotalMatchesRemaining() <= 0) {
        ui->signButton->show();
        ui->declineSignButton->show();

        ui->extensionWidget->hide();
        ui->extensionSalaryLabel->hide();
        ui->salaryLabel->hide();

        ui->signSalaryLabel->show();
        ui->signSalaryLabel->setText("Sign per Match: $" + QString::number(wrestler->calcSalary()));

        ui->matchesRemainingLabel->hide();

        disconnect(ui->signButton, nullptr, nullptr, nullptr);
        connect(ui->signButton, &QPushButton::clicked, this, [this, wrestler]() {
            wrestler->signContract(10);
            wrestler->setAffiliation(1);
            m_playerRoster.append(wrestler);
            m_freeAgents.removeOne(wrestler);

            updateWrestlerDetails(wrestler);
            populateWrestlerList(*m_currentRoster);
        });
        connect(ui->declineSignButton, &QPushButton::clicked, this, &MainWindow::declineSign);
    } else{
        ui->signButton->hide();
        ui->declineSignButton->hide();
        ui->signSalaryLabel->hide();

        ui->extensionSalaryLabel->show();
        ui->extensionWidget->show();
        ui->salaryLabel->show();
        ui->matchesRemainingLabel->show();

        ui->extensionSalaryLabel->setText("Projected Salary per Match: $" + QString::number(wrestler->calcSalary()));

        ui->extendContractSpinBox->setValue(5); // default 5 matches
        ui->extendContractSpinBox->setMinimum(1);
        ui->extendContractSpinBox->setMaximum(52);

        // hides info for resigning if wrestler is signed to someone other than player
        if (wrestler->getAffiliation() != 1){
            ui->extensionWidget->hide();
            ui->extensionSalaryLabel->hide();
            ui->signSalaryLabel->hide();
        }

        disconnect(ui->resignButton, nullptr, nullptr, nullptr); // safety
        connect(ui->resignButton, &QPushButton::clicked, this, [this, wrestler]() {
            int matches = ui->extendContractSpinBox->value();
            wrestler->signContract(matches); // Adds a new segment
            updateWrestlerDetails(wrestler); // Refresh everything
        });
    }


}
void MainWindow::on_editNameButton_clicked()
{
    ui->wrestlerNamelineEdit->setReadOnly(false);
    ui->wrestlerNamelineEdit->setFocus();
    ui->editNameButton->hide();
    ui->saveNameButton->show();
}
void MainWindow::on_saveNameButton_clicked()
{
    ui->wrestlerNamelineEdit->setReadOnly(true);
    ui->saveNameButton->hide();
    ui->editNameButton->show();
}

// Version for me
/*
QStringList MainWindow::loadFaceFiles(bool isFemale) {
    QString folder = isFemale ? "faces/women" : "faces/men";
    QDir dir(folder);
    return dir.entryList(QStringList() << "*.png" << "*.jpg" << "*.svg", QDir::Files);
}
QString MainWindow::randomFace(const QStringList &faces, bool isFemale) {
    if (faces.isEmpty()) return QString();

    std::mt19937 &gen = RandomUtils::getGenerator();
    std::uniform_int_distribution<> dis(0, faces.size() - 1);
    int index = dis(gen);

    QString folder = isFemale ? "faces/women" : "faces/men";
    return QDir(folder).filePath(faces[index]);
}

*/

// Painfully simple version for distribution/publishing/other people trying it out
QStringList MainWindow::loadFaceFiles(bool isFemale) {
    if (isFemale) {
        return {
            ":/faces/women/facesjs-w1.png",
            ":/faces/women/facesjs-w2.png",
            ":/faces/women/facesjs-w3.png",
            ":/faces/women/facesjs-w4.png",
            ":/faces/women/facesjs-w5.png",
            ":/faces/women/facesjs-w6.png",
            ":/faces/women/facesjs-w7.png",
            ":/faces/women/facesjs-w8.png",
            ":/faces/women/facesjs-w9.png",
            ":/faces/women/facesjs-w10.png",
            ":/faces/women/facesjs-w11.png",
        };
    } else {
        return {
            ":/faces/men/facesjs-m1.png",
            ":/faces/men/facesjs-m2.png",
            ":/faces/men/facesjs-m3.png",
            ":/faces/men/facesjs-m4.png",
            ":/faces/men/facesjs-m5.png",
            ":/faces/men/facesjs-m6.png",
            ":/faces/men/facesjs-m7.png",
            ":/faces/men/facesjs-m8.png",
            ":/faces/men/facesjs-m9.png",
            ":/faces/men/facesjs-m10.png",
            ":/faces/men/facesjs-m11.png",
            ":/faces/men/facesjs-m12.png",
            ":/faces/men/facesjs-m13.png",
            ":/faces/men/facesjs-m14.png",
            ":/faces/men/facesjs-m15.png",
            ":/faces/men/facesjs-m16.png",
            ":/faces/men/facesjs-m17.png",
        };
    }
}

QString MainWindow::randomFace(const QStringList &faces) {
    if (faces.isEmpty()) return QString();

    std::mt19937 &gen = RandomUtils::getGenerator();
    std::uniform_int_distribution<> dis(0, faces.size() - 1);
    int index = dis(gen);

    return faces[index];
}


void MainWindow::populateInjuredWrestlersList( QList<Wrestler*> &wrestlers) {
    QWidget* previousContainer = ui->injuryScrollArea->widget();
    if (previousContainer) {
        delete previousContainer;
    }

    // Create a container widget and layout for injured wrestlers
    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setAlignment(Qt::AlignTop);

    // Legend Layout
    QHBoxLayout *legendLayout = new QHBoxLayout;
    QLabel *popularityLabel = new QLabel("Popularity");
    QLabel *nameLabel = new QLabel("Name");
    QLabel *injuryLabel = new QLabel("Weeks Injured");
    QLabel *ageLabel = new QLabel("Age");

    // Set bold and underlined style for the legend
    QString legendStyle = QString("font-weight: bold; text-decoration: underline; color: %1; font-size: 18px;")
                              .arg(m_textColor.name());

    popularityLabel->setStyleSheet(legendStyle);
    nameLabel->setStyleSheet(legendStyle);
    injuryLabel->setStyleSheet(legendStyle);
    ageLabel->setStyleSheet(legendStyle);

    // Add labels to legend layout
    legendLayout->addWidget(popularityLabel);
    legendLayout->addWidget(nameLabel);
    legendLayout->addWidget(injuryLabel);
    legendLayout->addWidget(ageLabel);

    layout->addLayout(legendLayout);  // Add legend to the top

    // Iterate over wrestlers and add only those who are injured
    for (Wrestler* wrestler : wrestlers) {
        if (wrestler->getInjury() > 0) {  // Show only injured wrestlers
            QHBoxLayout *hLayout = new QHBoxLayout;

            // Popularity Label
            QLabel *popularityValue = new QLabel(QString::number(wrestler->getPopularity()));
            popularityValue->setStyleSheet(QString("color: %1")
                                               .arg(m_textColor.name()));

            // Name Button with Injury Icon
            QPushButton *nameButton = new QPushButton(wrestler->getName());
            nameButton->setIcon(injuredIconRed); // Set the injury icon
            nameButton->setIconSize(QSize(20, 20)); // Adjust icon size as needed
            nameButton->setStyleSheet("QPushButton {"
                                      "border: none;"
                                      "background: transparent;"
                                      "text-align: left;"
                                      "color: red;" // Highlight injured wrestlers
                                      "font-size: 16px;"
                                      "}");
            nameButton->setCursor(Qt::PointingHandCursor);
            // Weeks Injured Label
            QLabel *injuryValue = new QLabel(QString::number(wrestler->getInjury()));
            injuryValue->setStyleSheet(QString("color: %1")
                                           .arg(m_textColor.name()));

            // Age Label
            QLabel *ageValue = new QLabel(QString::number(wrestler->getAge()));
            ageValue->setStyleSheet(QString("color: %1")
                                        .arg(m_textColor.name()));

            // Connect the button to update wrestler details
            connect(nameButton, &QPushButton::clicked, this, [this, wrestler]() {
                ui->stackedWidget->setCurrentWidget(ui->wrestlerStats);
                updateWrestlerDetails(wrestler);
            });

            // Add widgets to row layout
            hLayout->addWidget(popularityValue);
            hLayout->addWidget(nameButton);
            hLayout->addWidget(injuryValue);
            hLayout->addWidget(ageValue);

            layout->addLayout(hLayout);
        }
    }

    // Apply layout to the container and set it in the injury scroll area
    container->setLayout(layout);
    //ui->injuryScrollWidgetContent->setLayout(layout);
    ui->injuryScrollArea->setWidget(container);
    ui->injuryScrollArea->setWidgetResizable(true);
}

// For sorting list of wrestlers
void MainWindow::sortWrestlers() {
    // Ensures a null pointer wont be sorted
    if (!m_currentRoster) { return;}

    QString selectedSort = ui->sortByAttributesCB->currentText();
    bool descending = ui->RosterDescendingSort->isChecked();

    // Sorting by what are probably the most relevant attributes
    std::sort(m_currentRoster->begin(), m_currentRoster->end(), [selectedSort, descending](Wrestler* a, Wrestler* b) {
        if (selectedSort == "Popularity") {
            return descending ? a->getPopularity() < b->getPopularity() : a->getPopularity() > b->getPopularity();
        } else if (selectedSort == "Name") {
            return descending ? a->getName() > b->getName() : a->getName() < b->getName();
        }  else if (selectedSort == "Health") {
            return descending ? a->getHealth() < b->getHealth() : a->getHealth() > b->getHealth();
        } else if (selectedSort == "Age") {
            return descending ? a->getAge() < b->getAge() : a->getAge() > b->getAge();
        } else if (selectedSort == "Salary") {
            return descending ? a->getSalary() < b->getSalary() : a->getSalary() > b->getSalary();
        } else if (selectedSort == "Role") {
            return descending ? a->getRole() < b->getRole() : a->getRole() > b->getRole();
        } else if (selectedSort == "Stamina") {
            return descending ? a->getStamina() < b->getStamina() : a->getStamina() > b->getStamina();
        } else if (selectedSort == "Charisma") {
            return descending ? a->getCharisma() < b->getCharisma() : a->getCharisma() > b->getCharisma();
        } else if (selectedSort == "Gender") {
            return descending ? a->isFemale() < b->isFemale() : a->isFemale() > b->isFemale();
        }
        return false;
    });

    populateWrestlerList(*m_currentRoster);
}
void MainWindow::on_RosterDescendingSort_toggled(bool checked)
{
    sortWrestlers();
}
void MainWindow::on_sortByAttributesCB_currentTextChanged(const QString &arg1)
{
    sortWrestlers();
}

// For signing new wrestlers
void MainWindow::on_ScoutTalentButton_clicked()
{
    scoutNewRecruit();  // function for getting young wrestlers
}
void MainWindow::scoutNewRecruit(){
    // either generates a new recruit, or shows recruit user scouted but didn't yet decline/sign
    if (!m_scoutedWrestler) {
        m_scoutedWrestler = new Wrestler();
        m_scoutedWrestler->setAffiliation(-1);  // -1 means scouted wrestler (will not be stored in database)

        // Sets the age to be younger than random generator in constructor
        std::uniform_int_distribution<> ageDist(18, 28);
        int randomAge = ageDist(RandomUtils::getGenerator());
        m_scoutedWrestler->setAge(randomAge);

        // Assign random face
        bool isFemale = m_scoutedWrestler->isFemale(); // Assuming you have this method
        QStringList faces = loadFaceFiles(isFemale);
        QString facePath = randomFace(faces);
        m_scoutedWrestler->setFacePath(facePath); // Assuming you have this setter

    }

    updateWrestlerDetails(m_scoutedWrestler);
    ui->stackedWidget->setCurrentWidget(ui->wrestlerStats);
}
void MainWindow::signNewRecruit(){
    if (!m_scoutedWrestler || m_scoutedWrestler->getTotalMatchesRemaining() > 0) { return; }

    m_playerRoster.append(m_scoutedWrestler);

    int matches = 10; // Always 10 matches for simplicity
    int salaryPerMatch = m_scoutedWrestler->calcSalary();
    ContractSegment initialSegment{matches, salaryPerMatch};
    m_scoutedWrestler->addContractSegment(initialSegment);

    m_scoutedWrestler->setAffiliation(1); // move them to player roster

    //QMessageBox::information(this, "Wrestler Signed", m_scoutedWrestler->getName() + " has been signed to your roster!");

    // updates buttons/contract info
    updateWrestlerDetails(m_scoutedWrestler);

    m_scoutedWrestler = nullptr;
}
void MainWindow::declineSign(){
    if (!m_scoutedWrestler || m_scoutedWrestler->getTotalMatchesRemaining() > 0) { return; }

    delete m_scoutedWrestler;
    m_scoutedWrestler = nullptr;

    ui->stackedWidget->setCurrentWidget(ui->Roster_Page);
}

// For CPU signing/resigning wrestlers
int MainWindow::evaluateWrestlerForCpu(Wrestler* w) {
    int score = 0;
    score += w->getPopularity();
    score += w->getCharisma() / 2;
    score += w->getStamina() / 2;

    if (w->getAge() > 40) score -= 10;

    // Random boost (0–5)
    std::mt19937& gen = RandomUtils::getGenerator();
    std::uniform_int_distribution<int> randBoost(0, 5);
    score += randBoost(gen);

    return score;
}
bool MainWindow::shouldCpuResign(Wrestler* w) {
    return evaluateWrestlerForCpu(w) >= 60;
}
void MainWindow::processCpuContracts() {

    std::mt19937& gen = RandomUtils::getGenerator();
    std::uniform_int_distribution<int> contractLength(10, 50);
    // CPU contracts last 10–40 weeks

    for (int i = m_cpuRoster.size() - 1; i >= 0; --i) {
        Wrestler* w = m_cpuRoster[i];

        if (w->getTotalMatchesRemaining() <= 0) { // contract expired
            if (shouldCpuResign(w)) {
                w->signContract(contractLength(gen));  // random length
            } else {
                m_cpuRoster.removeAt(i);
                w->setAffiliation(0); // free agent
                m_freeAgents.append(w);
            }
        }
    }
}
void MainWindow::cpuSignFreeAgents(int minRosterSize) {
    std::mt19937& gen = RandomUtils::getGenerator();
    std::uniform_real_distribution<> chance(0.0, 1.0);

    std::uniform_int_distribution<int> contractLength(10, 40);

    while (m_cpuRoster.size() < minRosterSize && !m_freeAgents.isEmpty()) {
        // First, rank all free agents
        QVector<std::pair<int, Wrestler*>> ranked;
        for (Wrestler* fa : m_freeAgents) {
            ranked.push_back({ evaluateWrestlerForCpu(fa), fa });
        }
        std::sort(ranked.begin(), ranked.end(),
                  [](auto& a, auto& b) { return a.first > b.first; });

        Wrestler* pick = nullptr;

        if (chance(gen) < 0.2 && ranked.size() > 1) {
            // 20% chance: pick someone from the top 3 instead of #1
            int idx = std::min(2, (int)ranked.size() - 1);
            std::uniform_int_distribution<int> pickRandom(0, idx);
            pick = ranked[pickRandom(gen)].second;
        } else {
            // Default: pick the best
            pick = ranked.front().second;
        }

        if (!pick) break;

        pick->signContract(contractLength(gen));  // Give them a random length cpntract
        pick->setAffiliation(2);   // CPU
        m_cpuRoster.append(pick);
        m_freeAgents.removeOne(pick);
    }
}

void MainWindow::updateCpuRosterWeekly() {
    // Decrement CPU contracts once per week (simulate 1 match/week)
    for (Wrestler* w : m_cpuRoster) {
        w->useOneMatch(); // same call used when booking a match
    }
    processCpuContracts();
    cpuSignFreeAgents(20); // keep at least 20 wrestlers
}

// Functions that show list of matches on show and edit matches
void MainWindow::populateMatchList( ) {
    ui->stackedWidget->setCurrentWidget(ui->Show_Card);
    QList<match>& matches = m_currentShow.getMatchesEdit();

    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    bool allMatchesValid = true;    // whether each match has valid number of participants
    const int buttonWidth = 100;  // or whatever consistent width you want

    // Clear previous widgets if any
    QWidget* previousContainer = ui->matchScrollArea->widget();
    if (previousContainer) {
        previousContainer->deleteLater();  // This will safely delete the old container and its children
    }

    for (int i = 0; i < matches.size(); ++i) {
        match& m = matches[i];

        QHBoxLayout *hLayout = new QHBoxLayout;

        // Display match type, participants, rating, etc.
        QLabel *matchTypeValue = new QLabel(m.getMatchType());
        matchTypeValue->setStyleSheet(QString("color: %1; font-size: 20px;")
                                          .arg(m_textColor.name()));

        matchTypeValue->setFixedWidth(buttonWidth);

        QString participantsList;

        const QList<Wrestler*> participants = m.getParticipants();
        if (participants.size() < 2) {
            allMatchesValid = false;
        }

        for (Wrestler* wrestler : m.getParticipants()) {
            if (wrestler) {  // Check if the pointer is not null
                if (!participantsList.isEmpty()) {
                    participantsList += ", ";  // Add a separator between names
                }
                participantsList += wrestler->getName();  // Get the name of the wrestler
            }
        }

        QLabel *participantsValue = new QLabel(participantsList);
        participantsValue->setStyleSheet(QString("color: %1; font-size: 18px;")
                                             .arg(m_textColor.name()));
        participantsValue->setWordWrap(true);
        participantsValue->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        QLabel *ratingValue = new QLabel(QString::number(m.getRating()) + " ★");

        // Edit Button
        QPushButton *editButton = new QPushButton("Edit");
        connect(editButton, &QPushButton::clicked, this, [this, &m, i ]() {
            openEditMatchPage(m, i);
        });
        editButton->setStyleSheet(
            "background-color: #0078D7; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;");
        editButton->setCursor(Qt::PointingHandCursor);

        // Remove Button
        QPushButton *removeButton = new QPushButton("Remove");
        connect(removeButton, &QPushButton::clicked, this, [this, i]() {
            m_currentShow.removeMatch(i);  // Remove match by index
            populateMatchList();
        });
        removeButton->setStyleSheet(
            "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;");
        removeButton->setCursor(Qt::PointingHandCursor);

        editButton->setFixedWidth(buttonWidth);
        removeButton->setFixedWidth(buttonWidth);

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

    // Disable finalize button if there are no matches or if any match has < 2 participants
    bool validShow = !matches.isEmpty() && allMatchesValid;
    ui->finalizeBooking->setEnabled(validShow);
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

        wrestlerComboBox->setStyleSheet(m_comboBoxStyle);

        wrestlerComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        wrestlerComboBox->setCursor(Qt::PointingHandCursor);

        // Create a new Remove button for the wrestler
        QPushButton* removeButton = new QPushButton("Remove", this);
        connect(removeButton, &QPushButton::clicked, this, [this, wrestlerComboBox]() {
            removeWrestlerFromMatch(wrestlerComboBox);  // Remove the selected wrestler ComboBox
        });
        // Remove button style is visible
        removeButton->setStyleSheet(
            "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;"
            );
        removeButton->setCursor(Qt::PointingHandCursor);

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
    updateMatchWrestlerSelection();
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

    // Populate with available wrestlers who are not injured
    QStringList wrestlerNames;
    for ( Wrestler* wrestler : m_playerRoster) {
        if (!selectedWrestlers.contains(wrestler->getName()) &&
            wrestler->getInjury() <= 0) {
            wrestlerNames.append(wrestler->getName());
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
    //ui->saveMatchDetails->setEnabled(uniqueWrestlers.size() >= 2);
}
void MainWindow::updateMatchWrestlerSelection() {
    if (!m_currentMatch) return;

    QSet<QString> selectedWrestlers;
    QGridLayout* layout = qobject_cast<QGridLayout*>(ui->participantLayout->layout());
    if (!layout) return;

    bool titleMatch = false;

    m_currentMatch->clearParticipants();

    // Loop through each block to find and set valid participants in the match
    for (int i = 0; i < layout->count(); ++i) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(layout->itemAt(i)->widget());
        if (comboBox) {
            QString wrestlerName = comboBox->currentText();
            for (Wrestler* wrestler : m_playerRoster) {
                // Again, ensures injured wrestlers don't competing
                if (wrestler->getName() == wrestlerName &&
                    wrestler->getInjury() <= 0) {
                    m_currentMatch->addWrestler(wrestler);
                    selectedWrestlers.insert(wrestlerName);
                    break;
                }
            }
        }
    }

    // Disconnect the signal to avoid recursion when updating the combo boxes
    for (int i = 0; i < layout->count(); ++i) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(layout->itemAt(i)->widget());
        if (comboBox) {
            disconnect(comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updateMatchWrestlerSelection);
        }
    }
    // Loop through each combo box in layout to set valid participants
    for (int i = 0; i < layout->count(); ++i) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(layout->itemAt(i)->widget());
        if (comboBox) {
            QString currentSelection = comboBox->currentText();  // Save the current selection
            bool isSelectedWrestlerValid = false;

            // Clear the combo box first
            comboBox->clear();

            // First, add currently selected wrestler back if it is valid and not injured
            for (Wrestler* wrestler : m_playerRoster) {
                if (wrestler->getName() == currentSelection && wrestler->getInjury() <= 0) {
                    if (isChampion(wrestler)) {
                        comboBox->addItem(QIcon(":/icons/myBasicTitle.png"), wrestler->getName());
                        titleMatch = true;
                    } else {
                        comboBox->addItem(wrestler->getName());
                    }

                    selectedWrestlers.insert(wrestler->getName());
                    isSelectedWrestlerValid = true;
                    break;  // No need to continue if selected wrestler already added
                }
            }
            // Add wrestlers who are not already selected and are not injured
            for (Wrestler* wrestler : m_playerRoster) {
                if (selectedWrestlers.find(wrestler->getName()) == selectedWrestlers.end() && wrestler->getInjury() <= 0) {
                    if (isChampion(wrestler)) {
                        comboBox->addItem(QIcon(":/icons/champ_icon.png"), wrestler->getName());
                        comboBox->setIconSize(QSize(24, 24));  // Or 40x40, or whatever you want

                    } else {
                        comboBox->addItem(wrestler->getName());
                    }

                }
            }

            // If the previously selected wrestler was valid, restore it as the current selection
            if (isSelectedWrestlerValid) {
                comboBox->setCurrentText(currentSelection);  // Restore the previous selection
            } else {
                comboBox->setCurrentIndex(0);  // Set to default option
            }
            // Update the selected wrestlers set
            selectedWrestlers.insert(currentSelection);
        }
    }
    // Reconnect the signal after the update is done
    for (int i = 0; i < layout->count(); ++i) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(layout->itemAt(i)->widget());
        if (comboBox) {
            connect(comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updateMatchWrestlerSelection);
        }
    }

    // Update the winnerComboBox
    ui->winnerComboBox->clear();
    // Add the "Random" option to the winnerComboBox
    ui->winnerComboBox->addItem("Random");

    for (Wrestler* wrestler : m_currentMatch->getParticipants()) {
        ui->winnerComboBox->addItem(wrestler->getName());
    }
    // Set the winner's combo box index to match winner's position in participants list
    Wrestler* winner = m_currentMatch->getWinner();
    if (winner) {
        int winnerIndex = -1;
        const QList<Wrestler*>& participants = m_currentMatch->getParticipants();

        // Find the winner's index in the participants list
        for (int i = 0; i < participants.size(); ++i) {
            if (participants[i]->getName() == winner->getName()) {
                winnerIndex = i;
                break;
            }
        }
        // If winner was found, set comboBox index to winner's position (plus 1 for "Random" option)
        if (winnerIndex != -1) {
            ui->winnerComboBox->setCurrentIndex(winnerIndex + 1);
        }
    }

    // updates and saves winner
    if (ui->winnerComboBox->currentText() == "Random") {
        m_currentMatch->setWinner(m_currentMatch->randomWinner());  // Set a random winner
    }
    else {
        // Otherwise, set the winner based on the ComboBox selection
        QString winnerName = ui->winnerComboBox->currentText();
        for (Wrestler* wrestler : m_playerRoster) {
            if (wrestler->getName() == winnerName) {
                m_currentMatch->setWinner(wrestler);
                break;
            }
        }
    }

    // Updates layout if tag team match
    if (ui->teamCheckBox->isChecked()) {
        updateTeamMatchLayout(true);  // Call function to update layout for team match
    }

    m_currentMatch->setChampionship(titleMatch &&
                                    ui->champCheckBox->isChecked());
    m_currentMatch->setTag(ui->teamCheckBox->isChecked());
}
void MainWindow::on_backFromEditMatch_clicked() {

    ui->stackedWidget->setCurrentWidget(ui->Show_Card);
    m_currentMatch->setChampionship(ui->champCheckBox->isChecked());
    m_currentMatch->setTag(ui->teamCheckBox->isChecked());
    m_currentMatch->setMatchType(ui->matchTypeComboBox->currentText());

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
        // Check if dark mode is active
        if (m_darkMode) {
            // Darker colors for dark mode
            ui->participantWidget->setStyleSheet(
                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
                "stop:0 #7B9FFF, stop:0.49 #7B9FFF, stop:0.50 #FF7F7F, stop:1 #FF7F7F);"
                );
        } else {
            // Lighter colors for light mode
            ui->participantWidget->setStyleSheet(
                "background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
                "stop:0 #A3C6FF, stop:0.49 #A3C6FF, stop:0.50 #FFB3B3, stop:1 #FFB3B3);"
                );
        }
        // Prevents combo boxes from getting the red/blue gradient
        for (int i = 0; i < layout->count(); ++i) {
            QWidget* widget = layout->itemAt(i)->widget();
            if (QComboBox* comboBox = qobject_cast<QComboBox*>(widget)) {
                comboBox->setStyleSheet(
                    "QComboBox {"
                    "    background-color: #FFFFFF;"  // Set a solid background color
                    "    color: #000000;"              // Black text for contrast
                    "    padding: 2px 10px;"
                    "    font-size: 14px;"
                    "}"
                    "QComboBox QAbstractItemView {"
                    "    background-color: #FFFFFF;"  // Background of the dropdown
                    "    color: #000000;"              // Text color in the dropdown
                    "}"
                    "QComboBox QScrollBar:vertical {"
                    "    background: transparent;" // Scrollbar itself remains transparent
                    "}"
                    "QComboBox QScrollBar::handle:vertical {"
                    "    background: #B0B0B0;" // Scrollbar handle color
                    "}"
                    );
            }
        }
    } else { ui->participantWidget->setStyleSheet(""); }

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

    for ( Wrestler* wrestler : m_playerRoster) {
        QVariant data = QVariant::fromValue(wrestler);

        // Add to all relevant combo boxes
        ui->worldChampComboBox->addItem(wrestler->getName(), data);
        ui->tagChampComboBox1->addItem(wrestler->getName(), data);
        ui->tagChampComboBox2->addItem(wrestler->getName(), data);
        if (wrestler->isFemale() == 1) {
            ui->womenChampComboBox->addItem(wrestler->getName(), data);
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

    // if user chooses 2 vacant championships
    if (!wrestler1 && !wrestler2){
        m_tag.setChampions({});
        return;
    }


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
bool MainWindow::isChampion( Wrestler* w)  {
    QString name = w->getName();

    Wrestler* worldChamp = m_world.getChampion();
    if (worldChamp && worldChamp->getName() == name) {
        return true;
    }

    Wrestler* womenChamp = m_women.getChampion();
    if (womenChamp && womenChamp->getName() == name) {
        return true;
    }

    const QList<Wrestler*>& tagChamps = m_tag.getChampions();
    for (Wrestler* champ : tagChamps) {
        if (champ && champ->getName() == name) {
            return true;
        }
    }

    return false;
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
    container->setStyleSheet(QString("color: %1; background-color: %2")
                                 .arg(m_textColor.name(), m_backgroundColor.name()));

    QWidget* previousContainer = ui->tagTeamScrollArea->widget();
    if (previousContainer) {
        previousContainer->deleteLater();  // Safe way to schedule deletion
    }

    for (int i = 0; i < m_teams.size(); ++i) {
        team& team = m_teams[i];

        QHBoxLayout* hLayout = new QHBoxLayout;
        QLabel* teamNameLabel = new QLabel(team.getTeamName());

        teamNameLabel->setStyleSheet(QString("color: %1; font-size: 20px;")
                                         .arg(m_textColor.name()));
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
        membersLabel->setStyleSheet(QString("color: %1; font-size: 20px;")
                                        .arg(m_textColor.name()));

        // Edit Button
        QPushButton* editButton = new QPushButton("Edit");
        connect(editButton, &QPushButton::clicked, this, [this, &team, i]() {
            openEditTeamPage(m_teams[i]);
        });

        editButton->setStyleSheet(
            "background-color: #0078D7; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;");
        editButton->setCursor(Qt::PointingHandCursor);

        // Remove Button
        QPushButton* removeButton = new QPushButton("Remove");
        connect(removeButton, &QPushButton::clicked, this, [this, i]() {
            removeTeam(i);
        });
        removeButton->setStyleSheet(
            "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;");
        removeButton->setCursor(Qt::PointingHandCursor);

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
        for ( Wrestler* w : m_playerRoster) {
            wrestlerComboBox->addItem(w->getName());
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
        wrestlerComboBox->setCursor(Qt::PointingHandCursor);

        QPushButton* removeButton = new QPushButton("Remove", this);
        connect(removeButton, &QPushButton::clicked, this, [this, wrestlerComboBox]() {
            removeWrestlerFromTeam(wrestlerComboBox);
        });

        removeButton->setStyleSheet(
            "background-color: #D32F2F; color: white; font-size: 16px; padding: 4px 8px; border-radius: 5px;" );
        removeButton->setCursor(Qt::PointingHandCursor);

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
    for ( Wrestler* wrestler : m_playerRoster) {
        if (!selectedWrestlers.contains(wrestler->getName())) {
            wrestlerNames.append(wrestler->getName());
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
    wrestlerComboBox->setCursor(Qt::PointingHandCursor);
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
    removeButton->setCursor(Qt::PointingHandCursor);

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
            for ( Wrestler* wrestler : m_playerRoster) {
                if (!selectedWrestlers.contains(wrestler->getName()) || wrestler->getName() == currentSelection) {
                    wrestlerNames.append(wrestler->getName());
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
                for (Wrestler* w : m_playerRoster) {
                    if (w->getName() == selectedWrestler) {
                        m_currentTeam->addMember(w);
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

// Functions for feuds/rivalries

void MainWindow::populateRivalryList() {
    ui->stackedWidget->setCurrentWidget(ui->rivalryPage);
    ui->newFeudWidget->hide();

    QGridLayout* layout = qobject_cast<QGridLayout*>(ui->feudScrollArea->layout());
    if (!layout) { return; }

    // Clear previous widgets
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }

    for (rivalry* rivalry : m_rivalries) {
        QWidget* rowWidget = new QWidget;
        QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);

        QString text = QString("%1 vs %2 (%3 matches left)")
                           .arg(rivalry->getWrestler1()->getName())
                           .arg(rivalry->getWrestler2()->getName())
                           .arg(rivalry->getWeeksLeft());

        QLabel* label = new QLabel(text);
        label->setStyleSheet(QString("color: %1;").arg(m_textColor.name()));

        rowLayout->addWidget(label);

        rowWidget->setLayout(rowLayout);
        layout->addWidget(rowWidget);
    }
}
void MainWindow::on_createFeudButton_clicked()
{
    ui->newFeudWidget->show();
    populateRivalryComboBoxes();
}
void MainWindow::on_startFeudButton_clicked()
{
    saveNewRivalry();
}
void MainWindow::saveNewRivalry() {
    int indexA = ui->feudWrestler1ComboBox->currentIndex();
    int indexB = ui->feudWrestler2ComboBox->currentIndex();

    populateRivalryComboBoxes();

    if (indexA < 0 || indexB < 0) {
        QMessageBox::warning(this, "Error", "Please select two wrestlers.");
        return;
    }

    Wrestler* a = m_availableRivalryWrestlers[indexA];
    Wrestler* b = m_availableRivalryWrestlers[indexB];

    if (a == b) {
        QMessageBox::warning(this, "Error", "A wrestler cannot feud with themselves.");
        return;
    }

    if (isDuplicateRivalry(a, b)) {
        QMessageBox::warning(this, "Error", "This rivalry already exists.");
        return;
    }

    m_rivalries.append(new rivalry(a, b));  // fixed to use `new`

    populateRivalryList(); // to refresh the rivalry display

}
void MainWindow::populateRivalryComboBoxes() {
    QList<Wrestler*> available = getAvailableWrestlersForRivalry();
    m_availableRivalryWrestlers = available;

    ui->feudWrestler1ComboBox->clear();
    ui->feudWrestler2ComboBox->clear();

    for (Wrestler* w : available) {
        ui->feudWrestler1ComboBox->addItem(w->getName(), QVariant::fromValue(w));
        ui->feudWrestler2ComboBox->addItem(w->getName(), QVariant::fromValue(w));
    }
}
QList<Wrestler*> MainWindow::getAvailableWrestlersForRivalry() const {
    QList<Wrestler*> available;

    for (Wrestler* wrestler : m_playerRoster) {
        bool inActiveRivalry = false;

        // Checks that wrestler is either not in a rivalry or is in a rivalry cooldown
        for (rivalry* rivalry : m_rivalries) {
            if (rivalry->getStatus() >= 2 &&
                (rivalry->getWrestler1()->getID() == wrestler->getID()
                 || rivalry->getWrestler2()->getID() == wrestler->getID())) {


                inActiveRivalry = true;
                break;
            }
        }

        if (!inActiveRivalry)
            available.append(wrestler);
    }

    return available;
}
bool MainWindow::isDuplicateRivalry(Wrestler* a, Wrestler* b) {
    for (const rivalry* r : m_rivalries) {
        if ((r->getWrestler1() == a && r->getWrestler2() == b) ||
            (r->getWrestler1() == b && r->getWrestler2() == a)) {
            return true;
        }
    }
    return false;
}

// Settings and Preferences
void MainWindow::on_darkModeCheckBox_stateChanged(int arg1)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);  // Show loading cursor
    m_darkMode = !m_darkMode;

    if (arg1 == Qt::Checked) {
        m_textColor = QColor("#F5F5F5") ;
        m_backgroundColor = QColor("#1E1E1E");
    } else {
        m_textColor = QColor("#1E1E1E");
        m_backgroundColor =  QColor("#F5F5F5") ;
    }
    applyTheme();  // Update UI elements with the new colors
    QApplication::restoreOverrideCursor();  // Return cursors to normal
}
void MainWindow::applyTheme(){
    // List of StackedWidget pages to exclude from background updates
    QList<QWidget*> excludedPages = { ui->useCustomRosterPage, ui->LandingPage, ui->newFilePage , ui->verticalWidget};

    // Iterate through all widgets inside the stacked widget
    for (QWidget* widget : ui->stackedWidget->findChildren<QWidget*>()) {
        // Skip buttons, combo boxes, scroll areas, excluded pages, and widgets that should be neither black or white
        if (qobject_cast<QPushButton*>(widget) ||
            qobject_cast<QComboBox*>(widget) ||
            qobject_cast<QScrollArea*>(widget) ||
            qobject_cast<QScrollBar*>(widget) ||
            excludedPages.contains(widget) ||
            widget == ui->participantLayout) {
            continue;
        }

        // Get the current font of the widget
        QFont widgetFont = widget->font();

        //  For labels, change the text color, not background
        if (qobject_cast<QLabel*>(widget)) {
            // Skip specific labels
            if (widget->objectName() == "injuredLabel") {
                continue; // Skip this label
            }
            widget->setStyleSheet(QString("color: %1;").arg(m_textColor.name()));
        }
        else if (qobject_cast<QFrame*>(widget)){
            // Set background color to m_textColor so it still shows up on screen
            widget->setStyleSheet(QString("background-color: %1;")
                                      .arg(m_textColor.name()));
        }
        else if (QCheckBox* checkbox = qobject_cast<QCheckBox*>(widget)) {
            QString checkBoxStyle = QString(
                                        "QCheckBox { color: %1; font-size: 14px; }"
                                        "QCheckBox::indicator { width: 16px; height: 16px; border: 2px solid %1; border-radius: 8px; background: transparent; }"
                                        "QCheckBox::indicator:checked { background: #0078D7; border: 2px solid #0055A4; }"
                                        ).arg(m_textColor.name());

            checkbox->setStyleSheet(checkBoxStyle);
        }
        else {
            // Apply both background and text color updates to other widgets
            widget->setStyleSheet(QString("background-color: %1; color: %2;")
                                      .arg(m_backgroundColor.name(), m_textColor.name()));
        }
        // Restore the original font after updating the style
        widget->setFont(widgetFont);
    }

    // Handle LineEdits separately to show they are interactable
    for (QLineEdit* lineEdit : ui->stackedWidget->findChildren<QLineEdit*>()) {
        if (lineEdit->objectName() != "excludeTheme") {
            lineEdit->setStyleSheet(QString("background-color: %1; color: %2; border: 1px solid gray; padding: 3px;")
                                        .arg(m_backgroundColor.name(), m_textColor.name()));
        }
    }
    applyScrollBarStyle();
}
void MainWindow::applyScrollBarStyle()
{
    for (QScrollBar* scrollBar : ui->stackedWidget->findChildren<QScrollBar*>()) {
        scrollBar->setStyleSheet(R"(
            QScrollBar:vertical {
                background: #E0E0E0;
                width: 14px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:vertical {
                background: #909090;
                min-height: 20px;
                border-radius: 4px;
            }
            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
                background: none;
                height: 0px;
            }
            QScrollBar:horizontal {
                background: #E0E0E0;
                height: 14px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:horizontal {
                background: #909090;
                min-width: 20px;
                border-radius: 4px;
            }
            QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
                background: none;
                width: 0px;
            }
        )");
    }
}
void MainWindow::clearData(){

    if (dataManager) {
        //dataManager->closeDatabase();
    }

    m_playerRoster.clear();
    m_lastUsedID = 0;

    m_world = championship();
    m_tag = championship();
    m_women = championship();

    m_teams.clear();
    m_currentTeam = nullptr;
    m_currentTeamIndex = -1;

    m_money = 0;
    m_fans = 0;
    m_year = 0;
    m_currentWeek = 0;

    m_currentShow.clear();
    m_currentMatch = nullptr;
    m_currentMatchIndex = -1;

    if (m_spacerItem) {
        delete m_spacerItem;
        m_spacerItem = nullptr;
    }

    m_moneyHistory.clear();
    m_fanHistory.clear();

    ui->stackedWidget->setCurrentWidget(ui->LandingPage);
}

// Functions for displaying wrestler face
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event); // always call base class first
    updateWrestlerImage();           // rescale pixmap to new label size
}
void MainWindow::updateWrestlerImage()
{
    if (m_currentFace.isNull()) {
        ui->wrestlerImage->clear();
        return;
    }

    ui->wrestlerImage->setPixmap(
        m_currentFace.scaled(ui->wrestlerImage->size(),
                              Qt::KeepAspectRatio,
                              Qt::SmoothTransformation)
        );
    ui->wrestlerImage->setAlignment(Qt::AlignCenter);
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->wrestlerImage && event->type() == QEvent::Resize) {
        updateWrestlerImage();
        return true; // handled
    }
    return QMainWindow::eventFilter(obj, event);
}



