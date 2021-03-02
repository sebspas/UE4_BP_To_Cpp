// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestMarker.h"

// Sets default values
AQuestMarker::AQuestMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	// Attach it to the scene
	SetRootComponent(Root);
	ParticleSystem->SetupAttachment(Root);
}

void AQuestMarker::RefreshVisibility()
{
	FQuestInfo Quest = GetQuestManager()->GetQuest(QuestName);
	bool Visibility = GetQuestManager()->IsActiveQuest(QuestName) && Quest.Progress == ShowAtProgress;
	ParticleSystem->SetVisibility(Visibility);
}

void AQuestMarker::BeginPlay()
{
	GetQuestManager()->CompletedQuest.AddDynamic(this, &AQuestMarker::QuestUpdated);
	RefreshVisibility();
}

void AQuestMarker::QuestUpdated(int32 Index)
{
	RefreshVisibility();
}
