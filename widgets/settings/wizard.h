#ifndef SETTINGS_WIZARD_H
#define SETTINGS_WIZARD_H

#include "../global.h"

#include <c++utilities/misc/flagenumclass.h>

#include <QWizard>
#include <QWizardPage>

#include <memory>

namespace QtGui {

class SetupDetection;

namespace Ui {
class MainConfigWizardPage;
class AutostartWizardPage;
} // namespace Ui

enum class MainConfiguration : std::uint64_t {
    None,
    CurrentlyRunning,
    LauncherExternal,
    LauncherBuiltIn,
    SystemdUserUnit,
    SystemdSystemUnit,
};

enum class ExtraConfiguration : std::uint64_t {
    None,
    SystemdIntegration = (1 << 0),
};

class SYNCTHINGWIDGETS_EXPORT Wizard : public QWizard {
    Q_OBJECT

public:
    explicit Wizard(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~Wizard() override;

    static Wizard *instance();
    SetupDetection &setupDetection();
    MainConfiguration mainConfig() const;
    ExtraConfiguration extraConfig() const;
    bool autoStart() const;

Q_SIGNALS:
    void settingsRequested();

private Q_SLOTS:
    void showDetailsFromSetupDetection();
    void handleConfigurationSelected(MainConfiguration mainConfig, ExtraConfiguration extraConfig);
    void handleAutostartSelected(bool autostartEnabled);

private:
    static Wizard *s_instance;
    std::unique_ptr<SetupDetection> m_setupDetection;
    MainConfiguration m_mainConfig = MainConfiguration::None;
    ExtraConfiguration m_extraConfig = ExtraConfiguration::None;
    bool m_autoStart = false;
};

inline MainConfiguration Wizard::mainConfig() const
{
    return m_mainConfig;
}

inline ExtraConfiguration Wizard::extraConfig() const
{
    return m_extraConfig;
}

inline bool Wizard::autoStart() const
{
    return m_autoStart;
}

class SYNCTHINGWIDGETS_EXPORT WelcomeWizardPage final : public QWizardPage {
    Q_OBJECT

public:
    explicit WelcomeWizardPage(QWidget *parent = nullptr);

    bool isComplete() const override;
};

class SYNCTHINGWIDGETS_EXPORT DetectionWizardPage final : public QWizardPage {
    Q_OBJECT

public:
    explicit DetectionWizardPage(QWidget *parent = nullptr);

    bool isComplete() const override;
    void initializePage() override;
    void cleanupPage() override;

public Q_SLOTS:
    void refresh();

private Q_SLOTS:
    void tryToConnect();
    void continueIfDone();

private:
    SetupDetection *m_setupDetection;
};

class SYNCTHINGWIDGETS_EXPORT MainConfigWizardPage final : public QWizardPage {
    Q_OBJECT

public:
    explicit MainConfigWizardPage(QWidget *parent = nullptr);
    ~MainConfigWizardPage() override;

    bool isComplete() const override;
    void initializePage() override;
    void cleanupPage() override;
    bool validatePage() override;

Q_SIGNALS:
    void retry();
    void configurationSelected(MainConfiguration mainConfig, ExtraConfiguration extraConfig);

private Q_SLOTS:
    void handleSelectionChanged();

private:
    std::unique_ptr<Ui::MainConfigWizardPage> m_ui;
    bool m_configSelected;
};

class SYNCTHINGWIDGETS_EXPORT AutostartWizardPage final : public QWizardPage {
    Q_OBJECT

public:
    explicit AutostartWizardPage(QWidget *parent = nullptr);
    ~AutostartWizardPage() override;

    bool isComplete() const override;
    void initializePage() override;
    void cleanupPage() override;
    bool validatePage() override;

Q_SIGNALS:
    void autostartSelected(bool autostartEnabled);

private:
    std::unique_ptr<Ui::AutostartWizardPage> m_ui;
    bool m_configSelected;
};

} // namespace QtGui

CPP_UTILITIES_MARK_FLAG_ENUM_CLASS(QtGui, QtGui::ExtraConfiguration)

#endif // SETTINGS_WIZARD_H