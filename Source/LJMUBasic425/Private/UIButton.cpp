#include "UIButton.h"

#include "Components/Button.h"

void UUIButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIButton::GetButtonReference(UButton* pButton)
{
	Button = pButton;
}
