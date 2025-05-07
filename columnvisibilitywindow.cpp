#include "columnvisibilitywindow.h"
#include "ui_columnvisibilitywindow.h"
#include <QSettings>

#include <QDebug>

columnvisibilitywindow::columnvisibilitywindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::columnvisibilitywindow)
{
    ui->setupUi(this);

    loadCheckBoxSettings();
}

columnvisibilitywindow::~columnvisibilitywindow()
{
    saveCheckBoxSettings();
    emit columnVisibilityWindowClosedSignal();
    delete ui;
}

void columnvisibilitywindow::saveCheckBoxSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Sawyer", "ProcessControlTool");
    settings.setValue("PidCheckBox", ui->PidcheckBox->isChecked());
    settings.setValue("NameCheckBox", ui->NamecheckBox->isChecked());
    settings.setValue("UmaskCheckBox", ui->UmaskcheckBox->isChecked());
    settings.setValue("StateCheckBox", ui->StatecheckBox->isChecked());
    settings.setValue("PPidCheckBox", ui->PPidcheckBox->isChecked());
    settings.setValue("TgidCheckBox", ui->TgidcheckBox->isChecked());
    settings.setValue("NgidCheckBox", ui->NgidcheckBox->isChecked());
    settings.setValue("TracerPidCheckBox", ui->TracerPidcheckBox->isChecked());
    settings.setValue("UidCheckBox", ui->UidcheckBox->isChecked());
    settings.setValue("GidCheckBox", ui->GidcheckBox->isChecked());
    settings.setValue("FDSizeCheckBox", ui->FDSizecheckBox->isChecked());
    settings.setValue("GroupsCheckBox", ui->GroupscheckBox->isChecked());
    settings.setValue("NStgidCheckBox", ui->NStgidcheckBox->isChecked());
    settings.setValue("NSpidCheckBox", ui->NSpidcheckBox->isChecked());
    settings.setValue("NSpgidCheckBox", ui->NSpgidcheckBox->isChecked());
    settings.setValue("NSsidCheckBox", ui->NSsidcheckBox->isChecked());
    settings.setValue("KthreadCheckBox", ui->KthreadcheckBox->isChecked());
    settings.setValue("VmPeakCheckBox", ui->VmPeakcheckBox->isChecked());
    settings.setValue("VmSizeCheckBox", ui->VmSizecheckBox->isChecked());
    settings.setValue("VmLckCheckBox", ui->VmLckcheckBox->isChecked());
    settings.setValue("VmPinCheckBox", ui->VmPincheckBox->isChecked());
    settings.setValue("VmHWMCheckBox", ui->VmHWMcheckBox->isChecked());
    settings.setValue("VmRSSCheckBox", ui->VmRSScheckBox->isChecked());
    settings.setValue("RssAnonCheckBox", ui->RssAnoncheckBox->isChecked());
    settings.setValue("RssFileCheckBox", ui->RssFilecheckBox->isChecked());
    settings.setValue("RssShmemCheckBox", ui->RssShmemcheckBox->isChecked());
    settings.setValue("VmDataCheckBox", ui->VmDatacheckBox->isChecked());
    settings.setValue("VmStkCheckBox", ui->VmStkcheckBox->isChecked());
    settings.setValue("VmExeCheckBox", ui->VmExecheckBox->isChecked());
    settings.setValue("VmLibCheckBox", ui->VmLibcheckBox->isChecked());
    settings.setValue("VmPTECheckBox", ui->VmPTEcheckBox->isChecked());
    settings.setValue("VmSwapCheckBox", ui->VmSwapcheckBox->isChecked());
    settings.setValue("HugetlbPagesCheckBox", ui->HugetlbPagescheckBox->isChecked());
    settings.setValue("CoreDumpingCheckBox", ui->CoreDumpingcheckBox->isChecked());
    settings.setValue("THP_enabledCheckBox", ui->THP_enabledcheckBox->isChecked());
    settings.setValue("untag_maskCheckBox", ui->untag_maskcheckBox->isChecked());
    settings.setValue("ThreadsCheckBox", ui->ThreadscheckBox->isChecked());
    settings.setValue("SigQCheckBox", ui->SigQcheckBox->isChecked());
    settings.setValue("SigPndCheckBox", ui->SigPndcheckBox->isChecked());
    settings.setValue("ShdPndCheckBox", ui->ShdPndcheckBox->isChecked());
    settings.setValue("SigBlkCheckBox", ui->SigBlkcheckBox->isChecked());
    settings.setValue("SigIgnCheckBox", ui->SigIgncheckBox->isChecked());
    settings.setValue("SigCgtCheckBox", ui->SigCgtcheckBox->isChecked());
    settings.setValue("CapInhCheckBox", ui->CapInhcheckBox->isChecked());
    settings.setValue("CapPrmCheckBox", ui->CapPrmcheckBox->isChecked());
    settings.setValue("CapEffCheckBox", ui->CapEffcheckBox->isChecked());
    settings.setValue("CapBndCheckBox", ui->CapBndcheckBox->isChecked());
    settings.setValue("CapAmbCheckBox", ui->CapAmbcheckBox->isChecked());
    settings.setValue("NoNewPrivsCheckBox", ui->NoNewPrivscheckBox->isChecked());
    settings.setValue("SeccompCheckBox", ui->SeccompcheckBox->isChecked());
    settings.setValue("Seccomp_filtersCheckBox", ui->Seccomp_filterscheckBox->isChecked());
    settings.setValue("Speculation_Store_BypassCheckBox", ui->Speculation_Store_BypasscheckBox->isChecked());
    settings.setValue("SpeculationIndirectBranchCheckBox", ui->SpeculationIndirectBranchcheckBox->isChecked());
    settings.setValue("Cpus_allowedCheckBox", ui->Cpus_allowedcheckBox->isChecked());
    settings.setValue("Cpus_allowed_listCheckBox", ui->Cpus_allowed_listcheckBox->isChecked());
    settings.setValue("Mems_allowedCheckBox", ui->Mems_allowedcheckBox->isChecked());
    settings.setValue("Mems_allowed_listCheckBox", ui->Mems_allowed_listcheckBox->isChecked());
    settings.setValue("voluntary_ctxt_switchesCheckBox", ui->voluntary_ctxt_switchescheckBox->isChecked());
    settings.setValue("nonvoluntary_ctxt_switchesCheckBox", ui->nonvoluntary_ctxt_switchescheckBox->isChecked());
    settings.setValue("x86_Thread_featuresCheckBox", ui->x86_Thread_featurescheckBox->isChecked());
    settings.setValue("x86_Thread_features_lockedCheckBox", ui->x86_Thread_features_lockedcheckBox->isChecked());
    settings.setValue("pgrpCheckBox", ui->pgrpcheckBox->isChecked());
    settings.setValue("sessionCheckBox", ui->sessioncheckBox->isChecked());
    settings.setValue("tty_nrCheckBox", ui->tty_nrcheckBox->isChecked());
    settings.setValue("tpgidCheckBox", ui->tpgidcheckBox->isChecked());
    settings.setValue("flagsCheckBox", ui->flagscheckBox->isChecked());
    settings.setValue("minfltCheckBox", ui->minfltcheckBox->isChecked());
    settings.setValue("cminfltCheckBox", ui->cminfltcheckBox->isChecked());
    settings.setValue("majfltCheckBox", ui->majfltcheckBox->isChecked());
    settings.setValue("cmajfltCheckBox", ui->cmajfltcheckBox->isChecked());
    settings.setValue("utimeCheckBox", ui->utimecheckBox->isChecked());
    settings.setValue("stimeCheckBox", ui->stimecheckBox->isChecked());
    settings.setValue("cutimeCheckBox", ui->cutimecheckBox->isChecked());
    settings.setValue("cstimeCheckBox", ui->cstimecheckBox->isChecked());
    settings.setValue("priorityCheckBox", ui->prioritycheckBox->isChecked());
    settings.setValue("niceCheckBox", ui->nicecheckBox->isChecked());
    settings.setValue("num_threadsCheckBox", ui->num_threadscheckBox->isChecked());
    settings.setValue("itrealvalueCheckBox", ui->itrealvaluecheckBox->isChecked());
    settings.setValue("starttimeCheckBox", ui->starttimecheckBox->isChecked());
    settings.setValue("vsizeCheckBox", ui->vsizecheckBox->isChecked());
    settings.setValue("rssCheckBox", ui->rsscheckBox->isChecked());
    settings.setValue("rsslimCheckBox", ui->rsslimcheckBox->isChecked());
    settings.setValue("startcodeCheckBox", ui->startcodecheckBox->isChecked());
    settings.setValue("endcodeCheckBox", ui->endcodecheckBox->isChecked());
    settings.setValue("startstackCheckBox", ui->startstackcheckBox->isChecked());
    settings.setValue("kstkespCheckBox", ui->kstkespcheckBox->isChecked());
    settings.setValue("kstkeipCheckBox", ui->kstkeipcheckBox->isChecked());
    settings.setValue("signalCheckBox", ui->signalcheckBox->isChecked());
    settings.setValue("blockedCheckBox", ui->blockedcheckBox->isChecked());
    settings.setValue("sigignoreCheckBox", ui->sigignorecheckBox->isChecked());
    settings.setValue("sigcatchCheckBox", ui->sigcatchcheckBox->isChecked());
    settings.setValue("wchanCheckBox", ui->wchancheckBox->isChecked());
    settings.setValue("nswapCheckBox", ui->nswapcheckBox->isChecked());
    settings.setValue("cnswapCheckBox", ui->cnswapcheckBox->isChecked());
    settings.setValue("exit_signalCheckBox", ui->exit_signalcheckBox->isChecked());
    settings.setValue("processorCheckBox", ui->processorcheckBox->isChecked());
    settings.setValue("rt_priorityCheckBox", ui->rt_prioritycheckBox->isChecked());
    settings.setValue("policyCheckBox", ui->policycheckBox->isChecked());
    settings.setValue("delayacct_blkio_ticksCheckBox", ui->delayacct_blkio_tickscheckBox->isChecked());
    settings.setValue("guest_timeCheckBox", ui->guest_timecheckBox->isChecked());
    settings.setValue("cguest_timeCheckBox", ui->cguest_timecheckBox->isChecked());
    settings.setValue("start_dataCheckBox", ui->start_datacheckBox->isChecked());
    settings.setValue("end_dataCheckBox", ui->end_datacheckBox->isChecked());
    settings.setValue("start_brkCheckBox", ui->start_brkcheckBox->isChecked());
    settings.setValue("arg_startCheckBox", ui->arg_startcheckBox->isChecked());
    settings.setValue("arg_endCheckBox", ui->arg_endcheckBox->isChecked());
    settings.setValue("env_startCheckBox", ui->env_startcheckBox->isChecked());
    settings.setValue("env_endCheckBox", ui->env_endcheckBox->isChecked());
    settings.setValue("exit_codeCheckBox", ui->exit_codecheckBox->isChecked());
}

void columnvisibilitywindow::loadCheckBoxSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Sawyer", "ProcessControlTool");
    ui->PidcheckBox->setChecked(settings.value("PidCheckBox").toBool());
    ui->NamecheckBox->setChecked(settings.value("NameCheckBox").toBool());
    ui->UmaskcheckBox->setChecked(settings.value("UmaskCheckBox").toBool());
    ui->StatecheckBox->setChecked(settings.value("StateCheckBox").toBool());
    ui->PPidcheckBox->setChecked(settings.value("PPidCheckBox").toBool());
    ui->TgidcheckBox->setChecked(settings.value("TgidCheckBox").toBool());
    ui->NgidcheckBox->setChecked(settings.value("NgidCheckBox").toBool());
    ui->TracerPidcheckBox->setChecked(settings.value("TracerPidCheckBox").toBool());
    ui->UidcheckBox->setChecked(settings.value("UidCheckBox").toBool());
    ui->GidcheckBox->setChecked(settings.value("GidCheckBox").toBool());
    ui->FDSizecheckBox->setChecked(settings.value("FDSizeCheckBox").toBool());
    ui->GroupscheckBox->setChecked(settings.value("GroupsCheckBox").toBool());
    ui->NStgidcheckBox->setChecked(settings.value("NStgidCheckBox").toBool());
    ui->NSpidcheckBox->setChecked(settings.value("NSpidCheckBox").toBool());
    ui->NSpgidcheckBox->setChecked(settings.value("NSpgidCheckBox").toBool());
    ui->NSsidcheckBox->setChecked(settings.value("NSsidCheckBox").toBool());
    ui->KthreadcheckBox->setChecked(settings.value("KthreadCheckBox").toBool());
    ui->VmPeakcheckBox->setChecked(settings.value("VmPeakCheckBox").toBool());
    ui->VmSizecheckBox->setChecked(settings.value("VmSizeCheckBox").toBool());
    ui->VmLckcheckBox->setChecked(settings.value("VmLckCheckBox").toBool());
    ui->VmPincheckBox->setChecked(settings.value("VmPinCheckBox").toBool());
    ui->VmHWMcheckBox->setChecked(settings.value("VmHWMCheckBox").toBool());
    ui->VmRSScheckBox->setChecked(settings.value("VmRSSCheckBox").toBool());
    ui->RssAnoncheckBox->setChecked(settings.value("RssAnonCheckBox").toBool());
    ui->RssFilecheckBox->setChecked(settings.value("RssFileCheckBox").toBool());
    ui->RssShmemcheckBox->setChecked(settings.value("RssShmemCheckBox").toBool());
    ui->VmDatacheckBox->setChecked(settings.value("VmDataCheckBox").toBool());
    ui->VmStkcheckBox->setChecked(settings.value("VmStkCheckBox").toBool());
    ui->VmExecheckBox->setChecked(settings.value("VmExeCheckBox").toBool());
    ui->VmLibcheckBox->setChecked(settings.value("VmLibCheckBox").toBool());
    ui->VmPTEcheckBox->setChecked(settings.value("VmPTECheckBox").toBool());
    ui->VmSwapcheckBox->setChecked(settings.value("VmSwapCheckBox").toBool());
    ui->HugetlbPagescheckBox->setChecked(settings.value("HugetlbPagesCheckBox").toBool());
    ui->CoreDumpingcheckBox->setChecked(settings.value("CoreDumpingCheckBox").toBool());
    ui->THP_enabledcheckBox->setChecked(settings.value("THP_enabledCheckBox").toBool());
    ui->untag_maskcheckBox->setChecked(settings.value("untag_maskCheckBox").toBool());
    ui->ThreadscheckBox->setChecked(settings.value("ThreadsCheckBox").toBool());
    ui->SigQcheckBox->setChecked(settings.value("SigQCheckBox").toBool());
    ui->SigPndcheckBox->setChecked(settings.value("SigPndCheckBox").toBool());
    ui->ShdPndcheckBox->setChecked(settings.value("ShdPndCheckBox").toBool());
    ui->SigBlkcheckBox->setChecked(settings.value("SigBlkCheckBox").toBool());
    ui->SigIgncheckBox->setChecked(settings.value("SigIgnCheckBox").toBool());
    ui->SigCgtcheckBox->setChecked(settings.value("SigCgtCheckBox").toBool());
    ui->CapInhcheckBox->setChecked(settings.value("CapInhCheckBox").toBool());
    ui->CapPrmcheckBox->setChecked(settings.value("CapPrmCheckBox").toBool());
    ui->CapEffcheckBox->setChecked(settings.value("CapEffCheckBox").toBool());
    ui->CapBndcheckBox->setChecked(settings.value("CapBndCheckBox").toBool());
    ui->CapAmbcheckBox->setChecked(settings.value("CapAmbCheckBox").toBool());
    ui->NoNewPrivscheckBox->setChecked(settings.value("NoNewPrivsCheckBox").toBool());
    ui->SeccompcheckBox->setChecked(settings.value("SeccompCheckBox").toBool());
    ui->Seccomp_filterscheckBox->setChecked(settings.value("Seccomp_filtersCheckBox").toBool());
    ui->Speculation_Store_BypasscheckBox->setChecked(settings.value("Speculation_Store_BypassCheckBox").toBool());
    ui->SpeculationIndirectBranchcheckBox->setChecked(settings.value("SpeculationIndirectBranchCheckBox").toBool());
    ui->Cpus_allowedcheckBox->setChecked(settings.value("Cpus_allowedCheckBox").toBool());
    ui->Cpus_allowed_listcheckBox->setChecked(settings.value("Cpus_allowed_listCheckBox").toBool());
    ui->Mems_allowedcheckBox->setChecked(settings.value("Mems_allowedCheckBox").toBool());
    ui->Mems_allowed_listcheckBox->setChecked(settings.value("Mems_allowed_listCheckBox").toBool());
    ui->voluntary_ctxt_switchescheckBox->setChecked(settings.value("voluntary_ctxt_switchesCheckBox").toBool());
    ui->nonvoluntary_ctxt_switchescheckBox->setChecked(settings.value("nonvoluntary_ctxt_switchesCheckBox").toBool());
    ui->x86_Thread_featurescheckBox->setChecked(settings.value("x86_Thread_featuresCheckBox").toBool());
    ui->x86_Thread_features_lockedcheckBox->setChecked(settings.value("x86_Thread_features_lockedCheckBox").toBool());
    ui->pgrpcheckBox->setChecked(settings.value("pgrpCheckBox").toBool());
    ui->sessioncheckBox->setChecked(settings.value("sessionCheckBox").toBool());
    ui->tty_nrcheckBox->setChecked(settings.value("tty_nrCheckBox").toBool());
    ui->tpgidcheckBox->setChecked(settings.value("tpgidCheckBox").toBool());
    ui->flagscheckBox->setChecked(settings.value("flagsCheckBox").toBool());
    ui->minfltcheckBox->setChecked(settings.value("minfltCheckBox").toBool());
    ui->cminfltcheckBox->setChecked(settings.value("cminfltCheckBox").toBool());
    ui->majfltcheckBox->setChecked(settings.value("majfltCheckBox").toBool());
    ui->cmajfltcheckBox->setChecked(settings.value("cmajfltCheckBox").toBool());
    ui->utimecheckBox->setChecked(settings.value("utimeCheckBox").toBool());
    ui->stimecheckBox->setChecked(settings.value("stimeCheckBox").toBool());
    ui->cutimecheckBox->setChecked(settings.value("cutimeCheckBox").toBool());
    ui->cstimecheckBox->setChecked(settings.value("cstimeCheckBox").toBool());
    ui->prioritycheckBox->setChecked(settings.value("priorityCheckBox").toBool());
    ui->nicecheckBox->setChecked(settings.value("niceCheckBox").toBool());
    ui->num_threadscheckBox->setChecked(settings.value("num_threadsCheckBox").toBool());
    ui->itrealvaluecheckBox->setChecked(settings.value("itrealvalueCheckBox").toBool());
    ui->starttimecheckBox->setChecked(settings.value("starttimeCheckBox").toBool());
    ui->vsizecheckBox->setChecked(settings.value("vsizeCheckBox").toBool());
    ui->rsscheckBox->setChecked(settings.value("rssCheckBox").toBool());
    ui->rsslimcheckBox->setChecked(settings.value("rsslimCheckBox").toBool());
    ui->startcodecheckBox->setChecked(settings.value("startcodeCheckBox").toBool());
    ui->endcodecheckBox->setChecked(settings.value("endcodeCheckBox").toBool());
    ui->startstackcheckBox->setChecked(settings.value("startstackCheckBox").toBool());
    ui->kstkespcheckBox->setChecked(settings.value("kstkespCheckBox").toBool());
    ui->kstkeipcheckBox->setChecked(settings.value("kstkeipCheckBox").toBool());
    ui->signalcheckBox->setChecked(settings.value("signalCheckBox").toBool());
    ui->blockedcheckBox->setChecked(settings.value("blockedCheckBox").toBool());
    ui->sigignorecheckBox->setChecked(settings.value("sigignoreCheckBox").toBool());
    ui->sigcatchcheckBox->setChecked(settings.value("sigcatchCheckBox").toBool());
    ui->wchancheckBox->setChecked(settings.value("wchanCheckBox").toBool());
    ui->nswapcheckBox->setChecked(settings.value("nswapCheckBox").toBool());
    ui->cnswapcheckBox->setChecked(settings.value("cnswapCheckBox").toBool());
    ui->exit_signalcheckBox->setChecked(settings.value("exit_signalCheckBox").toBool());
    ui->processorcheckBox->setChecked(settings.value("processorCheckBox").toBool());
    ui->rt_prioritycheckBox->setChecked(settings.value("rt_priorityCheckBox").toBool());
    ui->policycheckBox->setChecked(settings.value("policyCheckBox").toBool());
    ui->delayacct_blkio_tickscheckBox->setChecked(settings.value("delayacct_blkio_ticksCheckBox").toBool());
    ui->guest_timecheckBox->setChecked(settings.value("guest_timeCheckBox").toBool());
    ui->cguest_timecheckBox->setChecked(settings.value("cguest_timeCheckBox").toBool());
    ui->start_datacheckBox->setChecked(settings.value("start_dataCheckBox").toBool());
    ui->end_datacheckBox->setChecked(settings.value("end_dataCheckBox").toBool());
    ui->start_brkcheckBox->setChecked(settings.value("start_brkCheckBox").toBool());
    ui->arg_startcheckBox->setChecked(settings.value("arg_startCheckBox").toBool());
    ui->arg_endcheckBox->setChecked(settings.value("arg_endCheckBox").toBool());
    ui->env_startcheckBox->setChecked(settings.value("env_startCheckBox").toBool());
    ui->env_endcheckBox->setChecked(settings.value("env_endCheckBox").toBool());
    ui->exit_codecheckBox->setChecked(settings.value("exit_codeCheckBox").toBool());
}



void columnvisibilitywindow::on_buttonBox_accepted()
{
    accept();
}

