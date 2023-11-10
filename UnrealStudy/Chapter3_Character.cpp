// Fill out your copyright notice in the Description page of Project Settings.


#include "Chapter3_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"

// Sets default values
AChapter3_Character::AChapter3_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//캡슐 콜리전의 크기를 설정한다.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//컨트롤러가 회전할 때 캐릭터는 회전하지 않도록 설정한다.
	//캐릭터가 카메라에 영향을 주도록 놔둔다
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	//캐릭터 무브먼트를 설정한다.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//카메라 붐을 생성한다 ( 충돌이 발생할 경우 플레이어 쪽으로 다가가도록 설정한다 )
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	//캐릭터를 다라다닐 카메라를 생성한다.
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f));

}

// Called when the game starts or when spawned
void AChapter3_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChapter3_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** Called for movement input */
void AChapter3_Character::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f)) {
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (InputValue.X != 0.0f) {
			const FVector RightDirection = UKismetMathLibrary::GetRightVector(YawRotation);

			AddMovementInput(RightDirection, InputValue.X);
		}

		if (InputValue.Y != 0.0f) {
			const FVector ForwardDirection = YawRotation.Vector();

			AddMovementInput(ForwardDirection, InputValue.Y);
		}
	}
}

void AChapter3_Character::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f)) {

		if (InputValue.X != 0.0f) {
			AddControllerYawInput(InputValue.X);
		}

		if (InputValue.Y != 0.0f) {
			AddControllerPitchInput(InputValue.Y);
		}
	}
}

//void AChapter3_Character::Jump(const FInputActionValue& Value)
//{
//	;
//}
//
//void AChapter3_Character::StopJumping(const FInputActionValue& Value)
//{
//	;
//}

// Called to bind functionality to input
void AChapter3_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedPlayerInputComponent != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		if (PlayerController != nullptr) {
			UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			EnhancedSubsystem->AddMappingContext(IC_Character, 1);
		}

		//코드를 추가할 위치
		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AChapter3_Character::Move);
		EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AChapter3_Character::Look);
		/*EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AChapter3_Character::Jump);
		EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AChapter3_Character::StopJumping);*/
	}

	

}

