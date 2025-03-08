/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QStackedWidget *stackedWidget;
    QWidget *LandingPage;
    QGridLayout *gridLayout_6;
    QWidget *verticalWidget;
    QGridLayout *gridLayout_5;
    QPushButton *StartNew;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *LoadGame;
    QWidget *newFilePage;
    QVBoxLayout *verticalLayout_2;
    QPushButton *backToLanding;
    QPushButton *randomRoster;
    QPushButton *customRoster;
    QPushButton *defaultRoster;
    QWidget *useCustomRosterPage;
    QWidget *Dashboard_Page;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_3;
    QLabel *moneyDisplay;
    QLabel *fansDisplay;
    QLabel *yearDisplay;
    QLabel *WeekDisplay;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *CardTab;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QWidget *Promotion_Page;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QWidget *moneyChart;
    QWidget *fanChart;
    QWidget *Roster_Page;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout_2;
    QPushButton *TeamsTab;
    QPushButton *ChampionTab;
    QPushButton *FeudsTab;
    QPushButton *ScoutTalentTab;
    QPushButton *InjuredTab;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *RosterDisplayTab;
    QWidget *viewRoster;
    QVBoxLayout *verticalLayout_7;
    QLabel *rosterLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QScrollBar *verticalScrollBar;
    QWidget *ChampionshipPage;
    QWidget *formLayoutWidget;
    QGridLayout *gridLayout_8;
    QLabel *womenChampLabel;
    QComboBox *womenChampComboBox;
    QLabel *worldChampLabel;
    QLabel *tagChampLabel;
    QComboBox *tagChampComboBox1;
    QComboBox *worldChampComboBox;
    QComboBox *tagChampComboBox2;
    QWidget *wrestlerStats;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *nameLabel;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *genderLabel;
    QLabel *ageLabel;
    QLabel *roleLabel;
    QPushButton *pushButton_2;
    QGridLayout *gridLayout;
    QLabel *staminaLabel;
    QLabel *brawlerLabel;
    QLabel *powerhouseLabel;
    QLabel *mmaLabel;
    QLabel *technicianLabel;
    QLabel *charismaLabel;
    QLabel *highFlyerLabel;
    QLabel *populatiryLabel;
    QWidget *Settings_Page;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *userSave;
    QSpacerItem *horizontalSpacer_3;
    QWidget *Show_Card;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *addMatchButton;
    QPushButton *finalizeBooking;
    QScrollArea *matchScrollArea;
    QWidget *widget;
    QScrollBar *verticalScrollBar_2;
    QWidget *matchSetup;
    QWidget *matchEditWidget;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QComboBox *winnerComboBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QComboBox *matchTypeComboBox;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *champCheckBox;
    QCheckBox *teamCheckBox;
    QWidget *participantLayout;
    QGridLayout *participantGridLayout;
    QPushButton *saveMatchDetails;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *addToMatch;
    QPushButton *removeFromMatch;
    QHBoxLayout *NavigationTabs;
    QPushButton *PromotionTab;
    QPushButton *DashboardTab;
    QPushButton *RosterTab;
    QPushButton *SettingsTab;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(790, 615);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(99);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMinimumSize(QSize(0, 450));
        stackedWidget->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        LandingPage = new QWidget();
        LandingPage->setObjectName("LandingPage");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LandingPage->sizePolicy().hasHeightForWidth());
        LandingPage->setSizePolicy(sizePolicy2);
        LandingPage->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        gridLayout_6 = new QGridLayout(LandingPage);
        gridLayout_6->setObjectName("gridLayout_6");
        verticalWidget = new QWidget(LandingPage);
        verticalWidget->setObjectName("verticalWidget");
        sizePolicy2.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy2);
        verticalWidget->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(30, 30, 30);"));
        gridLayout_5 = new QGridLayout(verticalWidget);
        gridLayout_5->setObjectName("gridLayout_5");
        StartNew = new QPushButton(verticalWidget);
        StartNew->setObjectName("StartNew");
        sizePolicy2.setHeightForWidth(StartNew->sizePolicy().hasHeightForWidth());
        StartNew->setSizePolicy(sizePolicy2);
        StartNew->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: 36pt \"Segoe UI\";"));

        gridLayout_5->addWidget(StartNew, 0, 1, 1, 1, Qt::AlignmentFlag::AlignVCenter);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_9, 0, 2, 1, 1);

        LoadGame = new QPushButton(verticalWidget);
        LoadGame->setObjectName("LoadGame");
        sizePolicy2.setHeightForWidth(LoadGame->sizePolicy().hasHeightForWidth());
        LoadGame->setSizePolicy(sizePolicy2);
        LoadGame->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: 36pt \"Segoe UI\";\n"
""));

        gridLayout_5->addWidget(LoadGame, 1, 1, 1, 1, Qt::AlignmentFlag::AlignVCenter);


        gridLayout_6->addWidget(verticalWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(LandingPage);
        newFilePage = new QWidget();
        newFilePage->setObjectName("newFilePage");
        sizePolicy2.setHeightForWidth(newFilePage->sizePolicy().hasHeightForWidth());
        newFilePage->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(newFilePage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        backToLanding = new QPushButton(newFilePage);
        backToLanding->setObjectName("backToLanding");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(backToLanding->sizePolicy().hasHeightForWidth());
        backToLanding->setSizePolicy(sizePolicy3);
        backToLanding->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 0, 0);\n"
"color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(backToLanding);

        randomRoster = new QPushButton(newFilePage);
        randomRoster->setObjectName("randomRoster");
        sizePolicy3.setHeightForWidth(randomRoster->sizePolicy().hasHeightForWidth());
        randomRoster->setSizePolicy(sizePolicy3);
        randomRoster->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: 30pt \"Segoe UI\";"));

        verticalLayout_2->addWidget(randomRoster, 0, Qt::AlignmentFlag::AlignHCenter);

        customRoster = new QPushButton(newFilePage);
        customRoster->setObjectName("customRoster");
        sizePolicy3.setHeightForWidth(customRoster->sizePolicy().hasHeightForWidth());
        customRoster->setSizePolicy(sizePolicy3);
        customRoster->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: 30pt \"Segoe UI\";"));

        verticalLayout_2->addWidget(customRoster, 0, Qt::AlignmentFlag::AlignHCenter);

        defaultRoster = new QPushButton(newFilePage);
        defaultRoster->setObjectName("defaultRoster");
        sizePolicy3.setHeightForWidth(defaultRoster->sizePolicy().hasHeightForWidth());
        defaultRoster->setSizePolicy(sizePolicy3);
        defaultRoster->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: 30pt \"Segoe UI\";"));

        verticalLayout_2->addWidget(defaultRoster, 0, Qt::AlignmentFlag::AlignHCenter);

        stackedWidget->addWidget(newFilePage);
        useCustomRosterPage = new QWidget();
        useCustomRosterPage->setObjectName("useCustomRosterPage");
        stackedWidget->addWidget(useCustomRosterPage);
        Dashboard_Page = new QWidget();
        Dashboard_Page->setObjectName("Dashboard_Page");
        Dashboard_Page->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gridLayout_7 = new QGridLayout(Dashboard_Page);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        moneyDisplay = new QLabel(Dashboard_Page);
        moneyDisplay->setObjectName("moneyDisplay");
        moneyDisplay->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));

        gridLayout_3->addWidget(moneyDisplay, 0, 0, 1, 1);

        fansDisplay = new QLabel(Dashboard_Page);
        fansDisplay->setObjectName("fansDisplay");
        fansDisplay->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));

        gridLayout_3->addWidget(fansDisplay, 1, 0, 1, 1);

        yearDisplay = new QLabel(Dashboard_Page);
        yearDisplay->setObjectName("yearDisplay");
        yearDisplay->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));

        gridLayout_3->addWidget(yearDisplay, 0, 1, 1, 1);

        WeekDisplay = new QLabel(Dashboard_Page);
        WeekDisplay->setObjectName("WeekDisplay");
        WeekDisplay->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));

        gridLayout_3->addWidget(WeekDisplay, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_3, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        CardTab = new QPushButton(Dashboard_Page);
        CardTab->setObjectName("CardTab");
        CardTab->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(CardTab->sizePolicy().hasHeightForWidth());
        CardTab->setSizePolicy(sizePolicy4);
        CardTab->setMaximumSize(QSize(250, 250));
        CardTab->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);\n"
"border: 3px solid black;\n"
"border-radius: 5px;\n"
"font: 24pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(CardTab, 0, Qt::AlignmentFlag::AlignVCenter);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_7->addLayout(horizontalLayout, 3, 0, 1, 1);

        pushButton = new QPushButton(Dashboard_Page);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout_7->addWidget(pushButton, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 90, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Ignored);

        gridLayout_7->addItem(verticalSpacer, 2, 0, 1, 1);

        stackedWidget->addWidget(Dashboard_Page);
        Promotion_Page = new QWidget();
        Promotion_Page->setObjectName("Promotion_Page");
        sizePolicy2.setHeightForWidth(Promotion_Page->sizePolicy().hasHeightForWidth());
        Promotion_Page->setSizePolicy(sizePolicy2);
        Promotion_Page->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_4 = new QVBoxLayout(Promotion_Page);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_2 = new QLabel(Promotion_Page);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 24pt \"Segoe UI\";"));

        verticalLayout_4->addWidget(label_2, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        moneyChart = new QWidget(Promotion_Page);
        moneyChart->setObjectName("moneyChart");
        sizePolicy2.setHeightForWidth(moneyChart->sizePolicy().hasHeightForWidth());
        moneyChart->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(moneyChart);

        fanChart = new QWidget(Promotion_Page);
        fanChart->setObjectName("fanChart");
        sizePolicy2.setHeightForWidth(fanChart->sizePolicy().hasHeightForWidth());
        fanChart->setSizePolicy(sizePolicy2);
        fanChart->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(170, 0, 0);"));

        horizontalLayout_4->addWidget(fanChart);


        verticalLayout_4->addLayout(horizontalLayout_4);

        stackedWidget->addWidget(Promotion_Page);
        Roster_Page = new QWidget();
        Roster_Page->setObjectName("Roster_Page");
        sizePolicy2.setHeightForWidth(Roster_Page->sizePolicy().hasHeightForWidth());
        Roster_Page->setSizePolicy(sizePolicy2);
        Roster_Page->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(Roster_Page);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label = new QLabel(Roster_Page);
        label->setObjectName("label");
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 28pt \"Segoe UI\";\n"
""));

        horizontalLayout_6->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(verticalSpacer_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(30);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        TeamsTab = new QPushButton(Roster_Page);
        TeamsTab->setObjectName("TeamsTab");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(TeamsTab->sizePolicy().hasHeightForWidth());
        TeamsTab->setSizePolicy(sizePolicy5);
        TeamsTab->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";\n"
"background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(TeamsTab, 1, 3, 1, 1);

        ChampionTab = new QPushButton(Roster_Page);
        ChampionTab->setObjectName("ChampionTab");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(ChampionTab->sizePolicy().hasHeightForWidth());
        ChampionTab->setSizePolicy(sizePolicy6);
        ChampionTab->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";\n"
"background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(ChampionTab, 0, 3, 1, 1);

        FeudsTab = new QPushButton(Roster_Page);
        FeudsTab->setObjectName("FeudsTab");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(FeudsTab->sizePolicy().hasHeightForWidth());
        FeudsTab->setSizePolicy(sizePolicy7);
        FeudsTab->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";\n"
"background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(FeudsTab, 1, 2, 1, 1);

        ScoutTalentTab = new QPushButton(Roster_Page);
        ScoutTalentTab->setObjectName("ScoutTalentTab");
        ScoutTalentTab->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"font: 20pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(ScoutTalentTab, 1, 1, 1, 1);

        InjuredTab = new QPushButton(Roster_Page);
        InjuredTab->setObjectName("InjuredTab");
        sizePolicy6.setHeightForWidth(InjuredTab->sizePolicy().hasHeightForWidth());
        InjuredTab->setSizePolicy(sizePolicy6);
        InjuredTab->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 20pt \"Segoe UI\";"));

        gridLayout_2->addWidget(InjuredTab, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        RosterDisplayTab = new QPushButton(Roster_Page);
        RosterDisplayTab->setObjectName("RosterDisplayTab");
        RosterDisplayTab->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 22pt \"Segoe UI\";"));

        horizontalLayout_5->addWidget(RosterDisplayTab);


        verticalLayout->addLayout(horizontalLayout_5);

        stackedWidget->addWidget(Roster_Page);
        viewRoster = new QWidget();
        viewRoster->setObjectName("viewRoster");
        viewRoster->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_7 = new QVBoxLayout(viewRoster);
        verticalLayout_7->setObjectName("verticalLayout_7");
        rosterLabel = new QLabel(viewRoster);
        rosterLabel->setObjectName("rosterLabel");
        rosterLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 20pt \"Segoe UI\";"));

        verticalLayout_7->addWidget(rosterLabel, 0, Qt::AlignmentFlag::AlignHCenter);

        scrollArea = new QScrollArea(viewRoster);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 203, 203);"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 66, 16));
        verticalScrollBar = new QScrollBar(scrollAreaWidgetContents);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(750, 0, 16, 381));
        verticalScrollBar->setOrientation(Qt::Orientation::Vertical);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_7->addWidget(scrollArea);

        stackedWidget->addWidget(viewRoster);
        ChampionshipPage = new QWidget();
        ChampionshipPage->setObjectName("ChampionshipPage");
        formLayoutWidget = new QWidget(ChampionshipPage);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(90, 40, 641, 371));
        gridLayout_8 = new QGridLayout(formLayoutWidget);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        womenChampLabel = new QLabel(formLayoutWidget);
        womenChampLabel->setObjectName("womenChampLabel");
        womenChampLabel->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));

        gridLayout_8->addWidget(womenChampLabel, 3, 0, 1, 1);

        womenChampComboBox = new QComboBox(formLayoutWidget);
        womenChampComboBox->setObjectName("womenChampComboBox");

        gridLayout_8->addWidget(womenChampComboBox, 3, 1, 1, 1);

        worldChampLabel = new QLabel(formLayoutWidget);
        worldChampLabel->setObjectName("worldChampLabel");
        worldChampLabel->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));

        gridLayout_8->addWidget(worldChampLabel, 0, 0, 1, 1);

        tagChampLabel = new QLabel(formLayoutWidget);
        tagChampLabel->setObjectName("tagChampLabel");
        tagChampLabel->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));

        gridLayout_8->addWidget(tagChampLabel, 1, 0, 1, 1);

        tagChampComboBox1 = new QComboBox(formLayoutWidget);
        tagChampComboBox1->setObjectName("tagChampComboBox1");

        gridLayout_8->addWidget(tagChampComboBox1, 1, 1, 1, 1);

        worldChampComboBox = new QComboBox(formLayoutWidget);
        worldChampComboBox->setObjectName("worldChampComboBox");

        gridLayout_8->addWidget(worldChampComboBox, 0, 1, 1, 1);

        tagChampComboBox2 = new QComboBox(formLayoutWidget);
        tagChampComboBox2->setObjectName("tagChampComboBox2");

        gridLayout_8->addWidget(tagChampComboBox2, 1, 2, 1, 1);

        stackedWidget->addWidget(ChampionshipPage);
        wrestlerStats = new QWidget();
        wrestlerStats->setObjectName("wrestlerStats");
        wrestlerStats->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_5 = new QVBoxLayout(wrestlerStats);
        verticalLayout_5->setObjectName("verticalLayout_5");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        nameLabel = new QLabel(wrestlerStats);
        nameLabel->setObjectName("nameLabel");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy8);
        nameLabel->setStyleSheet(QString::fromUtf8("font: 24pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(nameLabel, 0, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        horizontalSpacer_5 = new QSpacerItem(80, 24, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        genderLabel = new QLabel(wrestlerStats);
        genderLabel->setObjectName("genderLabel");
        QSizePolicy sizePolicy9(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(genderLabel->sizePolicy().hasHeightForWidth());
        genderLabel->setSizePolicy(sizePolicy9);
        genderLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 16pt \"Segoe UI\";"));

        verticalLayout_3->addWidget(genderLabel, 0, Qt::AlignmentFlag::AlignHCenter);

        ageLabel = new QLabel(wrestlerStats);
        ageLabel->setObjectName("ageLabel");
        sizePolicy9.setHeightForWidth(ageLabel->sizePolicy().hasHeightForWidth());
        ageLabel->setSizePolicy(sizePolicy9);
        ageLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        verticalLayout_3->addWidget(ageLabel, 0, Qt::AlignmentFlag::AlignHCenter);

        roleLabel = new QLabel(wrestlerStats);
        roleLabel->setObjectName("roleLabel");
        sizePolicy9.setHeightForWidth(roleLabel->sizePolicy().hasHeightForWidth());
        roleLabel->setSizePolicy(sizePolicy9);
        roleLabel->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(roleLabel, 0, Qt::AlignmentFlag::AlignHCenter);


        gridLayout_4->addLayout(verticalLayout_3, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(wrestlerStats);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setEnabled(true);
        sizePolicy3.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy3);
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(pushButton_2, 0, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        staminaLabel = new QLabel(wrestlerStats);
        staminaLabel->setObjectName("staminaLabel");
        staminaLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(staminaLabel, 5, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        brawlerLabel = new QLabel(wrestlerStats);
        brawlerLabel->setObjectName("brawlerLabel");
        brawlerLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(brawlerLabel, 2, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        powerhouseLabel = new QLabel(wrestlerStats);
        powerhouseLabel->setObjectName("powerhouseLabel");
        powerhouseLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(powerhouseLabel, 1, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        mmaLabel = new QLabel(wrestlerStats);
        mmaLabel->setObjectName("mmaLabel");
        mmaLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(mmaLabel, 5, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        technicianLabel = new QLabel(wrestlerStats);
        technicianLabel->setObjectName("technicianLabel");
        technicianLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(technicianLabel, 4, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        charismaLabel = new QLabel(wrestlerStats);
        charismaLabel->setObjectName("charismaLabel");
        charismaLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(charismaLabel, 3, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        highFlyerLabel = new QLabel(wrestlerStats);
        highFlyerLabel->setObjectName("highFlyerLabel");
        highFlyerLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(highFlyerLabel, 3, 1, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        populatiryLabel = new QLabel(wrestlerStats);
        populatiryLabel->setObjectName("populatiryLabel");
        populatiryLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 18pt \"Segoe UI\";"));

        gridLayout->addWidget(populatiryLabel, 1, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);


        verticalLayout_5->addLayout(gridLayout);

        stackedWidget->addWidget(wrestlerStats);
        Settings_Page = new QWidget();
        Settings_Page->setObjectName("Settings_Page");
        sizePolicy2.setHeightForWidth(Settings_Page->sizePolicy().hasHeightForWidth());
        Settings_Page->setSizePolicy(sizePolicy2);
        Settings_Page->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        horizontalLayoutWidget_3 = new QWidget(Settings_Page);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(-10, 300, 791, 80));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        userSave = new QPushButton(horizontalLayoutWidget_3);
        userSave->setObjectName("userSave");
        userSave->setStyleSheet(QString::fromUtf8("background-color: rgb(40, 40, 126);\n"
"font: 36pt \"Segoe UI\";"));

        horizontalLayout_3->addWidget(userSave, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        stackedWidget->addWidget(Settings_Page);
        Show_Card = new QWidget();
        Show_Card->setObjectName("Show_Card");
        sizePolicy2.setHeightForWidth(Show_Card->sizePolicy().hasHeightForWidth());
        Show_Card->setSizePolicy(sizePolicy2);
        Show_Card->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        horizontalLayoutWidget_2 = new QWidget(Show_Card);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(-11, 0, 801, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 22pt \"Segoe UI\";\n"
""));
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_5);

        horizontalLayoutWidget = new QWidget(Show_Card);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(30, 370, 310, 80));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        addMatchButton = new QPushButton(horizontalLayoutWidget);
        addMatchButton->setObjectName("addMatchButton");
        sizePolicy1.setHeightForWidth(addMatchButton->sizePolicy().hasHeightForWidth());
        addMatchButton->setSizePolicy(sizePolicy1);
        addMatchButton->setMaximumSize(QSize(16777215, 100));
        addMatchButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 18pt \"Segoe UI\";"));

        horizontalLayout_7->addWidget(addMatchButton);

        finalizeBooking = new QPushButton(horizontalLayoutWidget);
        finalizeBooking->setObjectName("finalizeBooking");
        sizePolicy1.setHeightForWidth(finalizeBooking->sizePolicy().hasHeightForWidth());
        finalizeBooking->setSizePolicy(sizePolicy1);
        finalizeBooking->setMaximumSize(QSize(16777215, 100));
        finalizeBooking->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 18pt \"Segoe UI\";"));

        horizontalLayout_7->addWidget(finalizeBooking);

        matchScrollArea = new QScrollArea(Show_Card);
        matchScrollArea->setObjectName("matchScrollArea");
        matchScrollArea->setGeometry(QRect(40, 70, 681, 291));
        matchScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 203, 203);"));
        matchScrollArea->setWidgetResizable(true);
        widget = new QWidget();
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 679, 289));
        verticalScrollBar_2 = new QScrollBar(widget);
        verticalScrollBar_2->setObjectName("verticalScrollBar_2");
        verticalScrollBar_2->setGeometry(QRect(750, 0, 16, 381));
        verticalScrollBar_2->setOrientation(Qt::Orientation::Vertical);
        matchScrollArea->setWidget(widget);
        stackedWidget->addWidget(Show_Card);
        matchSetup = new QWidget();
        matchSetup->setObjectName("matchSetup");
        matchEditWidget = new QWidget(matchSetup);
        matchEditWidget->setObjectName("matchEditWidget");
        matchEditWidget->setGeometry(QRect(10, 10, 761, 431));
        sizePolicy2.setHeightForWidth(matchEditWidget->sizePolicy().hasHeightForWidth());
        matchEditWidget->setSizePolicy(sizePolicy2);
        gridLayout_9 = new QGridLayout(matchEditWidget);
        gridLayout_9->setObjectName("gridLayout_9");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_4 = new QLabel(matchEditWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_9->addWidget(label_4);

        winnerComboBox = new QComboBox(matchEditWidget);
        winnerComboBox->setObjectName("winnerComboBox");

        horizontalLayout_9->addWidget(winnerComboBox);


        gridLayout_9->addLayout(horizontalLayout_9, 1, 3, 2, 2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_3 = new QLabel(matchEditWidget);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy10(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy10);

        horizontalLayout_8->addWidget(label_3);

        matchTypeComboBox = new QComboBox(matchEditWidget);
        matchTypeComboBox->addItem(QString());
        matchTypeComboBox->addItem(QString());
        matchTypeComboBox->addItem(QString());
        matchTypeComboBox->addItem(QString());
        matchTypeComboBox->setObjectName("matchTypeComboBox");

        horizontalLayout_8->addWidget(matchTypeComboBox);


        gridLayout_9->addLayout(horizontalLayout_8, 0, 2, 1, 3);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        champCheckBox = new QCheckBox(matchEditWidget);
        champCheckBox->setObjectName("champCheckBox");

        verticalLayout_8->addWidget(champCheckBox);

        teamCheckBox = new QCheckBox(matchEditWidget);
        teamCheckBox->setObjectName("teamCheckBox");

        verticalLayout_8->addWidget(teamCheckBox);


        gridLayout_9->addLayout(verticalLayout_8, 3, 4, 1, 1);

        participantLayout = new QWidget(matchEditWidget);
        participantLayout->setObjectName("participantLayout");
        sizePolicy2.setHeightForWidth(participantLayout->sizePolicy().hasHeightForWidth());
        participantLayout->setSizePolicy(sizePolicy2);
        participantGridLayout = new QGridLayout(participantLayout);
        participantGridLayout->setObjectName("participantGridLayout");

        gridLayout_9->addWidget(participantLayout, 0, 0, 3, 2);

        saveMatchDetails = new QPushButton(matchEditWidget);
        saveMatchDetails->setObjectName("saveMatchDetails");
        saveMatchDetails->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 20pt \"Segoe UI\";"));

        gridLayout_9->addWidget(saveMatchDetails, 4, 4, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        addToMatch = new QPushButton(matchEditWidget);
        addToMatch->setObjectName("addToMatch");
        addToMatch->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 20pt \"Segoe UI\";"));

        horizontalLayout_10->addWidget(addToMatch);

        removeFromMatch = new QPushButton(matchEditWidget);
        removeFromMatch->setObjectName("removeFromMatch");
        removeFromMatch->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 20pt \"Segoe UI\";"));

        horizontalLayout_10->addWidget(removeFromMatch);


        gridLayout_9->addLayout(horizontalLayout_10, 4, 0, 1, 1);

        stackedWidget->addWidget(matchSetup);

        verticalLayout_6->addWidget(stackedWidget);

        NavigationTabs = new QHBoxLayout();
        NavigationTabs->setSpacing(0);
        NavigationTabs->setObjectName("NavigationTabs");
        NavigationTabs->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        PromotionTab = new QPushButton(centralwidget);
        PromotionTab->setObjectName("PromotionTab");
        sizePolicy8.setHeightForWidth(PromotionTab->sizePolicy().hasHeightForWidth());
        PromotionTab->setSizePolicy(sizePolicy8);
        PromotionTab->setMaximumSize(QSize(16777215, 100));
        PromotionTab->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 22pt \"Segoe UI\";"));

        NavigationTabs->addWidget(PromotionTab);

        DashboardTab = new QPushButton(centralwidget);
        DashboardTab->setObjectName("DashboardTab");
        sizePolicy8.setHeightForWidth(DashboardTab->sizePolicy().hasHeightForWidth());
        DashboardTab->setSizePolicy(sizePolicy8);
        DashboardTab->setMaximumSize(QSize(16777215, 100));
        DashboardTab->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 22pt \"Segoe UI\";"));

        NavigationTabs->addWidget(DashboardTab);

        RosterTab = new QPushButton(centralwidget);
        RosterTab->setObjectName("RosterTab");
        sizePolicy1.setHeightForWidth(RosterTab->sizePolicy().hasHeightForWidth());
        RosterTab->setSizePolicy(sizePolicy1);
        RosterTab->setMaximumSize(QSize(16777215, 100));
        RosterTab->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 22pt \"Segoe UI\";"));

        NavigationTabs->addWidget(RosterTab);

        SettingsTab = new QPushButton(centralwidget);
        SettingsTab->setObjectName("SettingsTab");
        sizePolicy8.setHeightForWidth(SettingsTab->sizePolicy().hasHeightForWidth());
        SettingsTab->setSizePolicy(sizePolicy8);
        SettingsTab->setMaximumSize(QSize(16777215, 100));
        SettingsTab->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"font: 22pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));

        NavigationTabs->addWidget(SettingsTab);


        verticalLayout_6->addLayout(NavigationTabs);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 790, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(11);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        StartNew->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        LoadGame->setText(QCoreApplication::translate("MainWindow", "Load Game", nullptr));
        backToLanding->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        randomRoster->setText(QCoreApplication::translate("MainWindow", "Use Random", nullptr));
        customRoster->setText(QCoreApplication::translate("MainWindow", "Use Custom", nullptr));
        defaultRoster->setText(QCoreApplication::translate("MainWindow", "Use Default", nullptr));
        moneyDisplay->setText(QCoreApplication::translate("MainWindow", "Money:", nullptr));
        fansDisplay->setText(QCoreApplication::translate("MainWindow", "Fans:", nullptr));
        yearDisplay->setText(QCoreApplication::translate("MainWindow", "Year: ", nullptr));
        WeekDisplay->setText(QCoreApplication::translate("MainWindow", "Week:", nullptr));
        CardTab->setText(QCoreApplication::translate("MainWindow", "Book Show", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Skip 26 weeks", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Your Promotion", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Roster", nullptr));
        TeamsTab->setText(QCoreApplication::translate("MainWindow", "Teams", nullptr));
        ChampionTab->setText(QCoreApplication::translate("MainWindow", "Champions", nullptr));
        FeudsTab->setText(QCoreApplication::translate("MainWindow", "Feuds", nullptr));
        ScoutTalentTab->setText(QCoreApplication::translate("MainWindow", "Scout Talent", nullptr));
        InjuredTab->setText(QCoreApplication::translate("MainWindow", "Injured List", nullptr));
        RosterDisplayTab->setText(QCoreApplication::translate("MainWindow", "View Roster", nullptr));
        rosterLabel->setText(QCoreApplication::translate("MainWindow", "Your Roster", nullptr));
        womenChampLabel->setText(QCoreApplication::translate("MainWindow", "Women's Championship", nullptr));
        worldChampLabel->setText(QCoreApplication::translate("MainWindow", "World Champion: ", nullptr));
        tagChampLabel->setText(QCoreApplication::translate("MainWindow", "Tag Team Championship", nullptr));
        nameLabel->setText(QString());
        genderLabel->setText(QCoreApplication::translate("MainWindow", "Division:", nullptr));
        ageLabel->setText(QCoreApplication::translate("MainWindow", "Age: ", nullptr));
        roleLabel->setText(QCoreApplication::translate("MainWindow", "Role:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Edit Name", nullptr));
        staminaLabel->setText(QCoreApplication::translate("MainWindow", "Stamina:", nullptr));
        brawlerLabel->setText(QCoreApplication::translate("MainWindow", "Brawler:", nullptr));
        powerhouseLabel->setText(QCoreApplication::translate("MainWindow", "Powerhouse:", nullptr));
        mmaLabel->setText(QCoreApplication::translate("MainWindow", "MMA:", nullptr));
        technicianLabel->setText(QCoreApplication::translate("MainWindow", "Technician", nullptr));
        charismaLabel->setText(QCoreApplication::translate("MainWindow", "Charisma:", nullptr));
        highFlyerLabel->setText(QCoreApplication::translate("MainWindow", "High Flyer:", nullptr));
        populatiryLabel->setText(QCoreApplication::translate("MainWindow", "Popularity:", nullptr));
        userSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Today's Show", nullptr));
        addMatchButton->setText(QCoreApplication::translate("MainWindow", "Add Match", nullptr));
        finalizeBooking->setText(QCoreApplication::translate("MainWindow", "Submit Booking", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Winner:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Match Type:", nullptr));
        matchTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Standard", nullptr));
        matchTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Steel Cage", nullptr));
        matchTypeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Ladder", nullptr));
        matchTypeComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Battle Royal", nullptr));

        champCheckBox->setText(QCoreApplication::translate("MainWindow", "Championship Match", nullptr));
        teamCheckBox->setText(QCoreApplication::translate("MainWindow", "Teams", nullptr));
        saveMatchDetails->setText(QCoreApplication::translate("MainWindow", "Save Match Details", nullptr));
        addToMatch->setText(QCoreApplication::translate("MainWindow", "Add Wrestler", nullptr));
        removeFromMatch->setText(QCoreApplication::translate("MainWindow", "Subtract Wrestler", nullptr));
        PromotionTab->setText(QCoreApplication::translate("MainWindow", "Your Promotion", nullptr));
        DashboardTab->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        RosterTab->setText(QCoreApplication::translate("MainWindow", "Roster", nullptr));
        SettingsTab->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
