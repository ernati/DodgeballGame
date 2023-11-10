# DodgeballGame
- 클래스 구조를 표와 텍스트로 표현해놓았습니다.
- 편하신 방법으로 보시면 됩니다.

## 클래스 구조 - 표
![DodgeballGame 클래스 사진](https://github.com/ernati/DodgeballGame/assets/31719912/9655f301-e247-4c57-895e-0a40ace3a269)




## 클래스 구조 - 텍스트
- 각 클래스 별로, 범주 구분을 위해 "==="를 사용합니다.

# UnrealStudyGameMode

- 역할 
    - Start Level과 InGame Level을 각각 맡을 
    BP_StartGameMode와 BP_InGameMode의 부모 클래스

==============================================================================

# Start_PlayerController

- 역할
    - 시작하면, 메인 메뉴를 띄우며, 사용자의 키보드 입력을 제한하고
        - UI와의 소통만 가능하게 한다.

# DodgeballPlayerController

- 역할
    - InGame에서 재시작화면과 HUD를 맡는다.
    - 게임에서 이기거나 패배하면, 재시작 화면을 띄운다.
    - 게임 진행 중, 캐릭터의 체력과 같은 정보들을 UI로 띄워준다.

==============================================================================

# DodgeballCharacter 클래스

- 유저의 입력에 따른 캐릭터의 움직임 및 행동
- 캐릭터의 체력
    - HealthComponent 클래스를 통해 구현
- 캐릭터의 상태
    - 데미지 입음
    - 죽음
        - HealthInterface 클래스를 통해 구현

# EnemyCharacter 클래스

==============================================================================

# HealthComponent 클래스

- 이 Component를 가지고 있는 클래스에 체력 정보를 추가 및 관리

# HealthInterface 클래스

- 체력과 관련된 함수를 담고 있는 클래스

==============================================================================

# Dodgeball 클래스

- 공이 플레이어 캐릭터에 충돌했을 때의 이벤트
- 충돌했을 때의 사운드 및 이펙트

# MainMenuWidget 클래스

- 유저에게 제공할 UI 클래스
