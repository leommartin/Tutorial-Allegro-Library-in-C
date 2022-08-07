#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>

int main()
{
    al_init();
    al_install_keyboard();

    // 30fps
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);   // garante q o jogo exe em vel const
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); // fila de eventos
    ALLEGRO_DISPLAY* disp = al_create_display(370, 200);  // cria um display AxB
    ALLEGRO_FONT* font = al_create_builtin_font(); // fonte embutida


    // reagir aos eventos de teclado, exibição e cronômetro
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event; // guarda a info de qual evento ocorreu

    al_start_timer(timer); // iniciamos o timer
    while(1)               // loop principal
    {
        al_wait_for_event(queue, &event); // execução do programa eh block ate um evento acontecer

        if(event.type == ALLEGRO_EVENT_TIMER) // tenporizador disparou um evento
            redraw = true;  // avança um quadro // nesse caso não avança pois é só uma tela
        else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break; // sai do laço caso user pressione tecla ou clica no x da janela(display)

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // limpa tela para preto
            al_draw_text(font, al_map_rgb(225, 55, 255), 0, 0, 0, "Hello world!");
            // escreve hello world em branco no canto sup esq da tela
            al_flip_display();
            // confirma o resultado
                        
            redraw = false;
            // resetamos redraw antes de desenhar o próximo frame
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}