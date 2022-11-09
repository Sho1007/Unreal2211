# Unreal2211
Unreal Portfolio (Horror)

# Doing
Dialogue Function   
> to convert to CPP
* 현재 HUD 등 Widget들은 CPP로 많이 변환함
* BP_PlayerCharacter에서 CheckInteract 할 때 정상적으로 인식이 안되고 있음 (아마 InteractInterface 부분이 제대로 인식을 못하는 것 같음)
    * cpp 함수로 통으로 바꿔서 Cast<IInteractInterface> 로 처리해서 해결해봐야겠음

> to do
* Need to Use Data Structure
* Need to Fix Interact UI (Press 'E' to Interact) -> 커서 사라지고, 해당 박스 보이게 하는게 깔끔할듯 (지금은 hit 될때마다 생성 중)
* Need to DialogueBox UI (Press 'E') -> DisplayLine 때만 보이고, Ask Question 때는 안보이게
