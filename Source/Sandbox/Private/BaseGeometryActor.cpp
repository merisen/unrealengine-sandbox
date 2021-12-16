// Created by merisen in MerisenLLC

#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

// local log category
DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	SetRootComponent(baseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	initLocation = GetActorLocation();
	// Learning: printig types into game console log
	printTypes();
	setObjectColor(gData.color);

	GetWorldTimerManager().SetTimer(timerHandle, this, &ABaseGeometryActor::onTimerFired, gData.timerRate, true);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	handleMovement();
}

void ABaseGeometryActor::printTypes()
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons number: %d, kills number: %i"), weapNum, killNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Is Dead: %d"), isDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Has weapon: %d"), static_cast<int>(isWeap));
	UE_LOG(LogBaseGeometry, Warning, TEXT("My custom log"));

	FString name = "Custom name";
	UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s"), *name);

	FString weaponNumSum = "Weapon num = " + FString::FromInt(weapNum);
	FString healthStr = "Health = " + FString::SanitizeFloat(health);
	FString isDeadStr = "Is dead = " + FString(isDead ? "true" : "false");

	FString allStats = FString::Printf(TEXT(" \n === All custom stats === \n %s \n %s \n %s"), *weaponNumSum, *healthStr, *isDeadStr);
	UE_LOG(LogBaseGeometry, Error, TEXT("%s"), *allStats);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, name);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, allStats, true, FVector2D(1.5f, 1.5f));

	FTransform transform = GetActorTransform();
	FVector location = transform.GetLocation();
	FRotator rotator = transform.Rotator();
	FVector scale = transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *rotator.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *scale.ToString());

	UE_LOG(LogBaseGeometry, Error, TEXT("Human Transform %s"), *transform.ToHumanReadableString());
}

void ABaseGeometryActor::handleMovement()
{
	switch (gData.moveType)
	{
	case EMovementType::Sin:
	{
		FVector currentLocation = GetActorLocation();
		float time = GetWorld()->GetTimeSeconds();
		currentLocation.Z = initLocation.Z + gData.amplitude * FMath::Sin(gData.frequency * time);
		SetActorLocation(currentLocation);
	}
	break;
	case EMovementType::Static: break;
	default: break;
	}
}

void ABaseGeometryActor::setObjectColor(const FLinearColor& color)
{
	UMaterialInstanceDynamic* dynMaterial = baseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (dynMaterial)
	{
		dynMaterial->SetVectorParameterValue("Color", color);
	}
}

void ABaseGeometryActor::onTimerFired()
{
	if (++timerCount <= maxTimerCount)
	{
		const FLinearColor fColor = FLinearColor::MakeRandomColor();
		setObjectColor(fColor);
		onColorChanged.Broadcast(fColor, GetName());
	}
	else
	{
		GetWorldTimerManager().ClearTimer(timerHandle);
		onTimerFinished.Broadcast(this);
	}
}

