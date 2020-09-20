#include <iostream>
#include <windowsx.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

using namespace std;

HINSTANCE hInst;
HBRUSH Brush;
COLORREF COLOR;

class BOTON{
    private:
        int X,Y;
        bool ColSI;
    public:
    BOTON(){
        X = 420;
        Y = 200;
        ColSI = 0;
    }
    bool VERIFICAR_NO(int x,int y){
        if(x>=X&&y>=Y&&x<X+80&&y<Y+40){
            return 1;
        }else{
            return 0;
        }
    }
    bool VERIFICAR_SI(int x,int y){
        if(x>=250&&y>=200&&x<330&&y<240){
            return 1;
        }else{
            return 0;
        }
    }
    void MODIFICAR(){
        X = rand() % 650;
        Y = rand() % 450;
    }
    void SetColSI(bool S){
        ColSI = S;
    }
    bool GetColSI(){
        return ColSI;
    }
    void MOSTRAR(HDC hdc){

        COLOR = SetTextColor(hdc, RGB(50,255,255));
        Brush=CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc,Brush);

        Rectangle(hdc,X,Y,X+80,Y+40);
        TextOut(hdc,X+30,Y+10,"NO",2);

        if(ColSI){
            Brush=CreateSolidBrush(RGB(50, 250, 250));
            SelectObject(hdc,Brush);
            COLOR = SetTextColor(hdc, RGB(10,10,10));
        }

        Rectangle(hdc,250,200,330,240);
        TextOut(hdc,283,210,"SI",2);

        DeleteObject(Brush);
    }
}A;

BOOL CALLBACK DlgWin(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_PAINT:
        {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc=BeginPaint(hwndDlg,&ps);
            SetBkMode(hdc, TRANSPARENT);
            EndPaint(hwndDlg,&ps);
        }
        return TRUE;

        case WM_CLOSE:
        {   EndDialog(hwndDlg, 0);
        }
        return TRUE;

    }
    return FALSE;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_MOUSEMOVE:{
            long xpos=GET_X_LPARAM(lParam);
            long ypos=GET_Y_LPARAM(lParam);

            if(A.VERIFICAR_NO(xpos,ypos)){
                A.MODIFICAR();
                InvalidateRect(hwndDlg,NULL,TRUE);
            }
            if(A.VERIFICAR_SI(xpos,ypos)){
                if(A.GetColSI()==0){
                    A.SetColSI(1);
                    InvalidateRect(hwndDlg,NULL,TRUE);
                }
            }else{
                if(A.GetColSI()==1){
                    A.SetColSI(0);
                    InvalidateRect(hwndDlg,NULL,TRUE);
                }
            }
        }
        return TRUE;
        case WM_PAINT:
            {
                HDC hdc;
                PAINTSTRUCT ps;
                hdc=BeginPaint(hwndDlg,&ps);
                SetBkMode(hdc, TRANSPARENT);
                A.MOSTRAR(hdc);
                EndPaint(hwndDlg,&ps);
            }
            return TRUE;
        case WM_LBUTTONDOWN:{
            long xpos=GET_X_LPARAM(lParam);
            long ypos=GET_Y_LPARAM(lParam);
            if(A.VERIFICAR_SI(xpos,ypos)){
                EndDialog(hwndDlg, 0);
                DialogBox(hInst, MAKEINTRESOURCE(DLG_WIN), NULL, (DLGPROC)DlgWin);
            }
        }
            return TRUE;
        case WM_INITDIALOG:
        {
            FreeConsole();
        }
        return TRUE;

        case WM_COMMAND:
        {   switch(LOWORD(wParam))
            {

            }
        }
            return TRUE;
    }
    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}

