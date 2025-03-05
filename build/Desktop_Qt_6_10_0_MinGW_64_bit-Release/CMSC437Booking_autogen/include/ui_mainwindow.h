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
    QWidget *wrestlerStats;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_4;
    QLabel *technicainLabel;
    QLabel *charismaLabel;
    QLabel *mmaLabel;
    QLabel *powerhouseLabel;
    QLabel *roleLabel;
    QVBoxLayout *verticalLayout_5;
    QLabel *nameLabel;
    QLabel *ageLabel;
    QLabel *staminaLabel;
    QLabel *populatiryLabel;
    QLabel *highFlyerLabel;
    QLabel *brawlerLabel;
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
    QPushButton *finalizeBooking;
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 752, 388));
        verticalScrollBar = new QScrollBar(scrollAreaWidgetContents);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(750, 0, 16, 381));
        verticalScrollBar->setOrientation(Qt::Orientation::Vertical);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_7->addWidget(scrollArea);

        stackedWidget->addWidget(viewRoster);
        wrestlerStats = new QWidget();
        wrestlerStats->setObjectName("wrestlerStats");
        verticalLayout_8 = new QVBoxLayout(wrestlerStats);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        technicainLabel = new QLabel(wrestlerStats);
        technicainLabel->setObjectName("technicainLabel");
        technicainLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(technicainLabel, 4, 1, 1, 1);

        charismaLabel = new QLabel(wrestlerStats);
        charismaLabel->setObjectName("charismaLabel");
        charismaLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(charismaLabel, 3, 0, 1, 1);

        mmaLabel = new QLabel(wrestlerStats);
        mmaLabel->setObjectName("mmaLabel");
        mmaLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(mmaLabel, 5, 1, 1, 1);

        powerhouseLabel = new QLabel(wrestlerStats);
        powerhouseLabel->setObjectName("powerhouseLabel");
        powerhouseLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(powerhouseLabel, 1, 1, 1, 1);

        roleLabel = new QLabel(wrestlerStats);
        roleLabel->setObjectName("roleLabel");

        gridLayout_4->addWidget(roleLabel, 0, 2, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        nameLabel = new QLabel(wrestlerStats);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setStyleSheet(QString::fromUtf8("font: 24pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_5->addWidget(nameLabel, 0, Qt::AlignmentFlag::AlignHCenter);

        ageLabel = new QLabel(wrestlerStats);
        ageLabel->setObjectName("ageLabel");
        ageLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout_5->addWidget(ageLabel, 0, Qt::AlignmentFlag::AlignHCenter);


        gridLayout_4->addLayout(verticalLayout_5, 0, 1, 1, 1);

        staminaLabel = new QLabel(wrestlerStats);
        staminaLabel->setObjectName("staminaLabel");
        staminaLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(staminaLabel, 5, 0, 1, 1);

        populatiryLabel = new QLabel(wrestlerStats);
        populatiryLabel->setObjectName("populatiryLabel");
        populatiryLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(populatiryLabel, 1, 0, 1, 1);

        highFlyerLabel = new QLabel(wrestlerStats);
        highFlyerLabel->setObjectName("highFlyerLabel");
        highFlyerLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(highFlyerLabel, 3, 1, 1, 1);

        brawlerLabel = new QLabel(wrestlerStats);
        brawlerLabel->setObjectName("brawlerLabel");
        brawlerLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(brawlerLabel, 2, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);


        verticalLayout_8->addLayout(verticalLayout_3);

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

        finalizeBooking = new QPushButton(Show_Card);
        finalizeBooking->setObjectName("finalizeBooking");
        finalizeBooking->setGeometry(QRect(300, 350, 181, 61));
        sizePolicy1.setHeightForWidth(finalizeBooking->sizePolicy().hasHeightForWidth());
        finalizeBooking->setSizePolicy(sizePolicy1);
        finalizeBooking->setMaximumSize(QSize(16777215, 100));
        finalizeBooking->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 59, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 18pt \"Segoe UI\";"));
        stackedWidget->addWidget(Show_Card);

        verticalLayout_6->addWidget(stackedWidget);

        NavigationTabs = new QHBoxLayout();
        NavigationTabs->setSpacing(0);
        NavigationTabs->setObjectName("NavigationTabs");
        NavigationTabs->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        PromotionTab = new QPushButton(centralwidget);
        PromotionTab->setObjectName("PromotionTab");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
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

        stackedWidget->setCurrentIndex(6);


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
        technicainLabel->setText(QCoreApplication::translate("MainWindow", "Technician", nullptr));
        charismaLabel->setText(QCoreApplication::translate("MainWindow", "Charisma:", nullptr));
        mmaLabel->setText(QCoreApplication::translate("MainWindow", "MMA:", nullptr));
        powerhouseLabel->setText(QCoreApplication::translate("MainWindow", "Powerhouse:", nullptr));
        roleLabel->setText(QCoreApplication::translate("MainWindow", "Role:", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        ageLabel->setText(QCoreApplication::translate("MainWindow", "Age: ", nullptr));
        staminaLabel->setText(QCoreApplication::translate("MainWindow", "Stamina:", nullptr));
        populatiryLabel->setText(QCoreApplication::translate("MainWindow", "Popularity:", nullptr));
        highFlyerLabel->setText(QCoreApplication::translate("MainWindow", "High Flyer:", nullptr));
        brawlerLabel->setText(QCoreApplication::translate("MainWindow", "Brawler:", nullptr));
        userSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Today's Show", nullptr));
        finalizeBooking->setText(QCoreApplication::translate("MainWindow", "Submit Booking", nullptr));
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
