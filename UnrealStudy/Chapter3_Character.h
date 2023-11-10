// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Chapter3_Character.generated.h"


UCLASS()
class UNREALSTUDY_API AChapter3_Character : public ACharacter
{
	GENERATED_BODY()

	//플레이어 카메라의 자리 표시자 역할을 담당하는 스프링 암 컴포넌트
	//레벨에 배치된 지오메트리에 가려졌을 때 카메라가 대처하는 방법을
	//자동으로 제어해 주기 대문에 이 컴포넌트를 사용하는 것을 권장한다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPS_Cam, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//캐릭터를 따라다닐 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPS_Cam, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//캐릭터의 입력을 위해 추가할 입력 콘텍스트
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IC_Character;

	//캐릭터의 입력을 수신하기 위한 입력 액션
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;

	//캐릭터의 입력을 수신하기 위한 입력 액션
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Look;

	/*UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Jump;*/

public:
	// Sets default values for this character's properties
	AChapter3_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	/*void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);*/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
