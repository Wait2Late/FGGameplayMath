// Fill out your copyright notice in the Description page of Project Settings.
#include "DebugStrings.h"

#include "StateDemonstrator.h"
#include "FGGameplayMath/Context/ContextHelpers.h"
#include "Engine/Canvas.h"

void FDebugTextDelegateHelper::DrawDebugLabels(UCanvas* Canvas, APlayerController* PlayerController)
{
	if(!Canvas)
		return;

	const auto OldDrawColor = Canvas->DrawColor;
	Canvas->SetDrawColor(FColor::White);

	const auto View = Canvas->SceneView;
	const auto Font = GEngine->GetSmallFont();

	auto DebugText = DebugLabels.GetData();

	for(int32 i = 0; i < DebugLabels.Num(); i++, ++DebugText)
	{
		if(View->ViewFrustum.IntersectSphere(DebugText->Location, 1.f))
		{
			const auto ScreenLocation = Canvas->Project(DebugText->Location);
			Canvas->DrawText(Font, DebugText->Text, ScreenLocation.X, ScreenLocation.Y);
		}
	}

	Canvas->SetDrawColor(OldDrawColor);
}

void FDebugTextDelegateHelper::SetupFromProxy(const FDebugSceneProxy* InSceneProxy)
{
	DebugLabels.Reset();
	DebugLabels.Append(InSceneProxy->ProxyData.DebugLabels);
}

UDebugStrings::UDebugStrings(const FObjectInitializer& ObjectInitializer)
{
	FEngineShowFlags::RegisterCustomShowFlag(TEXT("DebugText"), false, SFG_Normal, FText::FromString("Debug Text"));
}

FDebugRenderSceneProxy* UDebugStrings::CreateDebugSceneProxy()
{
	FDebugSceneProxyData ProxyData;

	ProxyData.DebugLabels.Reset();

	if(const auto StateDemonstrator = Cast<AStateDemonstrator>(GetOwner()))
	{
		for(const auto Actor : StateDemonstrator->Demonstrators)
		{
			if(const auto TargetDemonstrator = Cast<AStateDemonstrator>(Actor))
			{
				if(StateDemonstrator == TargetDemonstrator)
					continue;
				
				auto RelativeContext = UContextHelpers::GetRelativeContext(StateDemonstrator, TargetDemonstrator);

				if(UContextHelpers::ContextPredicate(RelativeContext, StateDemonstrator->Context))
				{
					const auto Item = FDebugText(
						TargetDemonstrator->GetActorLocation(),
						FString("Checks out: " + TargetDemonstrator->GetName())
					);
		
					ProxyData.DebugLabels.Add(Item);
				}
				else
				{
					const auto Item = FDebugText(
						TargetDemonstrator->GetActorLocation(),
						FString("Doesn't: " + TargetDemonstrator->GetName())
					);
		
					ProxyData.DebugLabels.Add(Item);
				}
			}
		}
	}
	else
	{
		const auto Item = FDebugText(
			GetOwner()->GetActorLocation(),
			GetOwner()->GetName()
			);
		
		ProxyData.DebugLabels.Add(Item);
	}

	const auto NewSceneProxy = new FDebugSceneProxy(this, &ProxyData);
	DebugDrawDelegateManager.SetupFromProxy(NewSceneProxy);

	return NewSceneProxy;
}

FBoxSphereBounds UDebugStrings::CalcBounds(const FTransform& LocalToWorld) const
{
	const auto Box = FBox(
		FVector(-1000, -1000, -1000),
		FVector(1000, 1000, 1000)
	);

	return FBoxSphereBounds(Box);
}