// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_MainMenuButton.h"


UPoppet_MainMenuButton::UPoppet_MainMenuButton()
{
	CheckFocusRate = 0.1f;
}

void UPoppet_MainMenuButton::Start()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CheckFocus, this, &UPoppet_MainMenuButton::CheckFocus, CheckFocusRate, true);
}

void UPoppet_MainMenuButton::CheckFocus()
{
	if (IsHovered()) {

		SetKeyboardFocus();
		SetButtonStyle(EPoppet_ButtonStyleType::ButtonStyleType_Mouse);
	}
	else {
		EPoppet_ButtonStyleType StyleTypeSelected = HasKeyboardFocus() ? EPoppet_ButtonStyleType::ButtonStyleType_KeySelected : EPoppet_ButtonStyleType::ButtonStyleType_KeyNotSelected;
		SetButtonStyle(StyleTypeSelected);
	}
}

void UPoppet_MainMenuButton::SetButtonStyle(EPoppet_ButtonStyleType NewStyleType)
{
	BP_SetButtonStyle(NewStyleType);
}
