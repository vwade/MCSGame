// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MCSGame : ModuleRules
{
    public MCSGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.AddRange(new string[] { "MCSGame/Utilities" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
        
        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}

/*markdown
vwade
> hey, quick question. if i wanted to retype each of the strings in AddRange as an array, say defined at the top of the file, and use that in place of writing each of the strings inline (which for me is a bit of a headache to read) how might i do that? I am somewhat unfamiliar with .cs syntax, but i am familiar with .c - so something adjacent to that would work a miracle. thanks!

GitHub Copilot
> You can define the string arrays at the top of your constructor and then use them in AddRange. Here’s how you can do it in C# (very similar to C, but with array initialization syntax):
> ```cs
public MCSGame(ReadOnlyTargetRules Target) : base(Target)
{
    PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

    string[] publicModules = { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" };
    string[] privateModules = { };
    string[] privateIncludePaths = { "MCSGame/Utilities" };

    PublicDependencyModuleNames.AddRange(publicModules);
    PrivateDependencyModuleNames.AddRange(privateModules);
    PrivateIncludePaths.AddRange(privateIncludePaths);

    // ... rest of your code
}
```
>This way, you can easily see and edit the arrays at the top, and the AddRange calls become much cleaner. Let me know if you want this change applied to your file!
*/