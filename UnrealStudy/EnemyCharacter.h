// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dodgeball.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UNREALSTUDY_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SightSource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ADodgeball> DodgeballClass;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	bool LookAtActor(AActor* TargetActor);
	/*bool CanSeeActor(const AActor* TargetActor) const;*/
	bool CanSeeActor_SweepTrace(const AActor* TargetActor) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bCanSeePlayer = false;
	bool bPreviousCanSeePlayer = false;

	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval = 2.0f;
	float ThrowingDelay = 0.5f;
	void ThrowDodgeball();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
