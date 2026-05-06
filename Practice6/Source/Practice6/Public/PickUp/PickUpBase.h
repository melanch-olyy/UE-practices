// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

UCLASS()
class PRACTICE6_API APickUpBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpBase();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* PickUpMeshComponent;
	
	UFUNCTION(BlueprintPure, Category = "PickUp")
	bool isPickUpActive() const;
	
	UFUNCTION(BlueprintCallable, Category = "PickUp")
	void SetPickUpActive(bool state);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool bIsActive;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
