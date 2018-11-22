import random,pygame,sys
from pygame.locals import*
import subprocess as sp

WHITE=(255,255,255)
GREEN=(0,255,0)
GRAY=(157,157,157)

SPEED=1.6*10
FPS=40
WINDOWWIDTH=1300
WINDOWHEIGHT=700

PE_COME=1
PE_GVUP=2
PE_IN=3
PE_OUT=4

EL_BASE=11
EL_OPEN=12
EL_CLOSE=13
EL_READY_UP=14
EL_READY_DOWN=15
EL_UP=16
EL_DOWN=17
EL_STOP_UP=18
EL_STOP_DOWN=19
EL_START_IDLE=20


DOOR_TIME=80
START_TIME=80
PEOPLE_MOVE_TIME=100

ACC_TIME=60
UP_FLOOR_TIME=204
DOWN_FLOOR_TIME=244
UP_DED_TIME=56
DOWN_DEC_TIME=92

CLOSING=0
CLOSED=1
OPENGING=2
OPENED=3

List=[]
People=[]
Elevator={}
PeoImg=[]
Q=[]
S=[]
RightQx=[]
RightSx=[]
UpButtom=[0,0,0,0,0]
DownButtom=[0,0,0,0,0]
CarButtom=[0,0,0,0,0]
CanSee=[]

def getRandomImg():
    i=random.randint(0,68)
    return PeoImg[i]

def GetEvent():
    p = sp.Popen("./Elevator_Simulation", stdin=sp.PIPE, stdout=sp.PIPE)
    while True:
        try:
            p.stdin.flush()
            t = p.stdout.readline().decode("ascii").strip()
            t=t.split()
            s=[]
            for i in range(5):
                s.append(int(t[i]))
            k=5
            for i in range(3):
                call=[]
                for j in range(5):
                    call.append(int(t[k]))
                    k+=1
                s.append(call)
            for i in range(5):
                s.append(int(t[k]))
                k+=1
            #print(s)
            event={}
            event["time"]=s[0]*4
            event["evType"]=s[1]
            event["floor"]=s[2]
            event["state"]=s[3]
            event["door"]=s[4]
            event["callCar"]=s[5]
            event["callUp"]=s[6]
            event["callDown"]=s[7]
            event["orderNum"]=s[8]-1
            #print(event)
            List.append(event)
            if event["evType"]==PE_COME:
                person={}
                person["arrive"]=s[9]*4
                person["giveUp"]=s[10]*4
                person["inFloor"]=s[11]
                person["outFloor"]=s[12]
                person["img"]=getRandomImg()
                person["position"]=[-40,(4-s[11])*140+40]
                person["dx"]=0
                People.append(person)
        except (IndexError, ValueError):
            break

def GetPeoPng():
    for i in range(69):
        picture="person"+str(i+1)+".png"
        PeoImg.append(pygame.image.load(picture))
        
def SetRightPosition():
    Sx=1250
    Qx=800
    for i in range(9):
        RightSx.append(Sx)
        Sx-=40
    for i in range(300):
        RightQx.append(Qx)
        Qx-=40

def Initial():
    GetPeoPng()
    GetEvent()
    SetRightPosition()
    Elevator["position"]=[900,3*140]
    Elevator["direction"]=0
    Elevator["door"]=CLOSED
    Elevator["moveTime"]=0
    Elevator["floor"]=1
    Elevator["img"]=pygame.image.load('Elevator.png')
    for i in range(5):
        Q.append([])

def drawPeople():
    delete=[]
    for i in CanSee:
        person=People[i]
        DISPLAYSURF.blit(person["img"],tuple(person["position"]))
        png="want"+str(person["outFloor"])+".png"
        DISPLAYSURF.blit(pygame.image.load(png),(person["position"][0],person["position"][1]-10))
        if person["position"][0]<-50:
            delete.append(i)
    for i in delete:
        CanSee.remove(i)

def drawElevator():
    DISPLAYSURF.blit(Elevator["img"],tuple(Elevator["position"]))
    if Elevator["door"]==OPENED:
        pygame.draw.rect(DISPLAYSURF,WHITE,(890,Elevator["position"][1]+5,15,130))
    elif Elevator["door"]!=CLOSED:
        pygame.draw.rect(DISPLAYSURF,GRAY,(890,Elevator["position"][1]+5,15,130))

def drawButtom():
    for i in range(5):
        png="num"+str(i)+str(CarButtom[i])+".png"
        DISPLAYSURF.blit(pygame.image.load(png),(950+i*40,Elevator["position"][1]+5))
        png="up"+str(UpButtom[i])+".png"
        DISPLAYSURF.blit(pygame.image.load(png),(850,(4-i)*140+5))
        png="down"+str(DownButtom[i])+".png"
        DISPLAYSURF.blit(pygame.image.load(png),(850,(4-i)*140+30))

def dealEvent():
    event=List[LNum]
    orderNum=event["orderNum"]
    person=People[orderNum]
    Elevator["floor"]=event["floor"]
    Elevator["door"]=event["door"]
    UpButtom[0:5]=event["callUp"][0:5]
    DownButtom[0:5]=event["callDown"][0:5]
    CarButtom[0:5]=event["callCar"][0:5]
    if event["evType"]==PE_GVUP:
        Q[person["inFloor"]].remove(orderNum)
        person["dx"]=-10*SPEED
    elif event["evType"]==PE_IN:
        pygame.draw.rect(DISPLAYSURF,GREEN,(890,Elevator["position"][1]+5,15,130))
        Q[person["inFloor"]].remove(orderNum)
        S.append(orderNum)
        person["dx"]=5*SPEED
    elif event["evType"]==PE_OUT:
        S.remove(orderNum)
        person["dx"]=-5*SPEED
    elif event["evType"]==EL_UP:
        Elevator["moveTime"]=UP_FLOOR_TIME/SPEED
        Elevator["direction"]=-0.69*SPEED
    elif event["evType"]==EL_DOWN:
        Elevator["moveTime"]=DOWN_FLOOR_TIME/SPEED
        Elevator["direction"]=0.57*SPEED
    elif event["evType"]==EL_STOP_UP or event["evType"]==EL_STOP_DOWN:
        Elevator["direction"]=0
        Elevator["position"][1]=(4-event["floor"])*140

def changePosition():
    #y
    Elevator["position"][1]=(4-Elevator["floor"])*140-Elevator["direction"]*Elevator["moveTime"]
    Elevator["moveTime"]-=1
    for i in S:
        People[i]["position"][1]=Elevator["position"][1]+40
    #x
    for i in CanSee:
        right=0
        for j in range(5):
            if i in Q[j]:
                k=int(Q[j].index(i))
                if People[i]["position"][0]!=RightQx[k] and RightQx[k]>-40:
                    People[i]["position"][0]+=People[i]["dx"]
                    if People[i]["position"][0]>RightQx[k]:
                        People[i]["position"][0]=RightQx[k]
                right=1
                break
        if right:
            continue
        if i in S:
            k=S.index(i)
            if People[i]["position"][0]!=RightSx[k]:
                People[i]["position"][0]+=People[i]["dx"]
                if People[i]["position"][0]>RightSx[k]:
                    People[i]["position"][0]=RightSx[k]
            continue
        People[i]["position"][0]+=People[i]["dx"]
    
def main():
    global FPSCLOCK,DISPLAYSURF,LNum,Time
    Time=-200
    LNum=0
    pygame.init()
    FPSCLOCK=pygame.time.Clock()
    DISPLAYSURF=pygame.display.set_mode((WINDOWWIDTH,WINDOWHEIGHT))
    pygame.display.set_caption('Elevator Simulation')
    BGImg=pygame.image.load('BackGround.png')
    Initial()
    AllpeNum=len(People)-1
    PeOrder=0
    
    while True:
        while PeOrder<AllpeNum:
            if People[PeOrder]["arrive"]-85<=Time:
                Q[People[PeOrder]["inFloor"]].append(PeOrder)
                CanSee.append(PeOrder)
                People[PeOrder]["dx"]=10*SPEED
                PeOrder+=1
            else:
                break
        while List[LNum]["time"]<=Time:
            DISPLAYSURF.blit(Elevator["img"],(0,0))
            dealEvent()
            LNum+=1
            
        DISPLAYSURF.blit(BGImg,(0,0))
        drawElevator()
        drawButtom()
        drawPeople()
        
        for event in pygame.event.get():
            if event.type==QUIT:
                pygame.quit()
                sys.exit()
        changePosition()

        if(Time<0):
            time=Time-40
        else:
            time=Time
        fontObj=pygame.font.Font('freesansbold.ttf',32)
        textSurfaceObj=fontObj.render(str(int(time/40))+"s",True,GREEN)
        textRectObj=textSurfaceObj.get_rect()
        textRectObj.center=(150,30)
        DISPLAYSURF.blit(textSurfaceObj,textRectObj)

        Time+=1*SPEED
        pygame.display.update()
        FPSCLOCK.tick(FPS)
        
if __name__=='__main__':
    main()
