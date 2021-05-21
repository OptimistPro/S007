#include <iostream>

int main()
{
    std::cout << "Hello World!\n";

    char s[256];
    char s2[256];

    char f[] = "%s";

    char fd[] = "%d\n";

    _asm {
        //ввод 1 строки
        lea esi, s
        push esi
        lea ecx, f
        push ecx
        call scanf
        add esp, 8
        mov ecx, -1
        dec esi
        //ввод 2 строки
        lea esi, s2
        push esi
        lea ecx, f
        push ecx
        call scanf
        add esp, 8
        mov ecx, -1
        dec esi
        //Поиск
        lea ebx, s
        dec ebx
        lea ecx, s2

        b1 :
        inc ebx
            mov al, [ebx]
            cmp al, 0
            je b5
            cmp [ecx], '?'// равны
            je b8
            cmp[ecx], '*'// равны
            je b13
            cmp al, [ecx]
            jnz b1
            mov edx, ebx

            b2 :
        inc ecx
            inc ebx
            cmp [ecx], '*'// равны
            je b12
            
            mov al, [ebx] // конец 1 строки
            cmp al, 0
            je b3
            mov al, [ecx] // конец 2 строки
            cmp al, 0
            je b4
            cmp al, '?'// равны
            je b2
            cmp al, [ebx] // равны
            je b2
            mov ebx, edx
            lea ecx, s2
            jmp b1

             b12:
            inc ecx
            mov esi, ecx
            mov edi, ebx
            

            b14:
            mov ebx,edi
            mov ecx,esi
           
            inc edi
                cmp[ecx], '*'
                je b12
            mov al, [ebx]
            cmp al, 0
            je b5
            cmp [ecx], '?'
            je b10
            cmp[ecx], 0
            je b4
            cmp al, [ecx]
            jnz b14
     
                b10:
            inc ecx
            inc ebx
               
            mov al, [ecx]
                cmp al, '*'
                je b12
                cmp al, 0
                je b16
            cmp al, [ebx] 
            je b10
            
            cmp al, '?'
            je b10
            
            
            mov al, [ebx] 
            cmp al, 0
            je b5
            jmp b14


                b16:
            mov al, [ebx]
            cmp al, 0
            je b4
            jmp b14

            b15:
            mov edx,edi
            mov ecx,esi
            jmp b2

                b11:
                mov ebx, edx
                lea ecx, s2
                jmp b1
            b8 :
        mov edx, ebx
            jmp b2

            b13 :
        mov edx, ebx
            jmp b12


            b3 :
        mov al, [ecx]
            cmp al, 0
            jne b5

            b4 :
        lea ebx, s
            //add ebx, -1
            sub edx, ebx
            push edx
            jmp b6
            //Вывод результата
            b5 :
        mov ebx, -1
            push ebx

            b6 :
        lea ebx, fd
            push ebx
            call printf
            add esp, 8
    }
}