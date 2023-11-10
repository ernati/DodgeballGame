// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
//#include "DrawDebugHelpers.h"
#include "DodgeballFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("SightSource"));
	SightSource->SetupAttachment(RootComponent);
	SightSource->SetRelativeLocation(FVector(10.0f, 0.0f, 80.0f));

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	//LookAtActor(PlayerCharacter);
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer) {
			//닷지볼 던지기를 시작한다
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemyCharacter::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		}


		else {
			//닷지볼 던지기를 멈춘다.
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}


	bPreviousCanSeePlayer = bCanSeePlayer;

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyCharacter::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr)
	{
		return false ;
	}

	const TArray<const AActor*> IgnoreActors = { this, TargetActor };

	//if (CanSeeActor(TargetActor)) {
	if (UDodgeballFunctionLibrary::CanSeeActor(  
	GetWorld(),
	SightSource->GetComponentLocation(),
	TargetActor,
	IgnoreActors)  ) {

		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		SetActorRotation(LookAtRotation);

		return true;
	}

	return false;

	/*if (CanSeeActor_SweepTrace(TargetActor)) {

		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		SetActorRotation(LookAtRotation);
	}*/
}

//bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor) const
//{
//	if (TargetActor == nullptr)
//	{
//		return false;
//	}
//
//	FHitResult Hit;
//
//	//FVector Start = GetActorLocation();
//
//	FVector End = TargetActor->GetActorLocation();
//
//	//ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
//	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
//
//
//	FCollisionQueryParams QueryParams;
//
//	QueryParams.AddIgnoredActor(this);
//	QueryParams.AddIgnoredActor(TargetActor);
//
//	//GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
//	GetWorld()->LineTraceSingleByChannel(Hit, SightSource->GetComponentLocation(), End, Channel, QueryParams);
//
//	DrawDebugLine(GetWorld(), SightSource->GetComponentLocation(), End, FColor::Red);
//
//	return !Hit.bBlockingHit;
//}

bool AEnemyCharacter::CanSeeActor_SweepTrace(const AActor* TargetActor) const
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	FHitResult Hit;

	FVector Start = GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	FQuat Rotation = FQuat::Identity;

	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;

	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.0f, 20.0f, 20.0f));

	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}

void AEnemyCharacter::ThrowDodgeball() {
	if (DodgeballClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.0f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);

	GetWorld()->SpawnActor<ADodgeball>(DodgeballClass, SpawnLocation, GetActorRotation());
}