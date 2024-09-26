#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIN_MARGIN 10.0f

static int winh = 650;
static int winw = 400;

static LfFont titlefont;

int balance = 1000;

int number1;
int number2;
int number3;

int number1random;
int number2random;
int number3random;

int bet_size = 10;

static void checkwin();
static void spinningnumbers();
static void renderspinbuttons(GLFWwindow* window);
static void renderbalance();
static void shuffle_digits(GLFWwindow* window);

static void checkwin(){
    if(number1 == number2 && number2 == number3){
        balance = balance + bet_size * 15;
    }
    else if(number1 == number2 || number2 == number3){
        balance = balance + bet_size * 3;
    }
    else{
        balance = balance - bet_size;
    }
}

static void spinningnumbers() {
    char number1_str[10], number2_str[10], number3_str[10];
    sprintf(number1_str, "%d", number1);
    sprintf(number2_str, "%d", number2);
    sprintf(number3_str, "%d", number3);

    lf_set_ptr_x_absolute(winw - 175);
    lf_set_ptr_y_absolute(winh - 450);
    LfUIElementProps props = lf_get_theme().text_props;
    props.border_width = 5.0f;
    props.border_color = (LfColor){255, 255, 255, 255};
    lf_push_style_props(props);
    lf_push_font(&titlefont);
    lf_text(number1_str);
    lf_pop_font();
    lf_set_line_should_overflow(false);
    lf_pop_style_props();

    lf_set_ptr_x_absolute(winw - 350);
    lf_set_ptr_y_absolute(winh - 450);
    props.border_width = 5.0f;
    props.border_color = (LfColor){255, 255, 255, 255};
    lf_push_style_props(props);
    lf_push_font(&titlefont);
    lf_text(number2_str);
    lf_pop_font();
    lf_set_line_should_overflow(false);
    lf_pop_style_props();

    lf_set_ptr_x_absolute(winw - 260);
    lf_set_ptr_y_absolute(winh - 450);
    props.border_width = 5.0f;
    props.border_color = (LfColor){255, 255, 255, 255};
    lf_push_style_props(props);
    lf_push_font(&titlefont);
    lf_text(number3_str);
    lf_pop_font();
    lf_set_line_should_overflow(false);
    lf_pop_style_props();
}

static void renderspinbuttons(GLFWwindow* window){
    {
    const float width = 160.0;
    lf_set_ptr_x_absolute(winw - width - WIN_MARGIN * 16.0f);
    lf_set_ptr_y_absolute(winh - 250);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;   props.margin_right = 0.0f;
    props.color = (LfColor){56, 224, 34,255};
    props.border_width = 0.0f;  props.corner_radius = 3.0f;
    lf_push_style_props(props);
    lf_set_line_should_overflow(false);
    if(lf_button_fixed("Spin!", width, -1) == LF_CLICKED){
        shuffle_digits(window);
        checkwin();
    }
    lf_pop_style_props();
    }   

    {
    lf_set_ptr_x_absolute(winw - 65 - WIN_MARGIN * 16.0f);
    lf_set_ptr_y_absolute(winh - 200);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;   props.margin_right = 0.0f;
    props.color = (LfColor){56, 224, 34,255};
    props.border_width = 0.0f;  props.corner_radius = 3.0f;
    lf_push_style_props(props);
    if(lf_button_fixed("+", 65, -1) == LF_CLICKED){
        if(bet_size >= balance || bet_size <= 0){

        }
        else{
            bet_size = bet_size + 10;
        }

    }
    lf_pop_style_props();
    }

    {
    lf_set_ptr_x_absolute(winw - 160 - WIN_MARGIN * 16.0f);
    lf_set_ptr_y_absolute(winh - 200);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;   props.margin_right = 0.0f;
    props.color = (LfColor){56, 224, 34,255};
    props.border_width = 0.0f;  props.corner_radius = 3.0f;
    lf_push_style_props(props);
    if(lf_button_fixed("-", 65, -1) == LF_CLICKED){
        if(bet_size >= balance || bet_size <= 10){

        }
        else{
            bet_size = bet_size - 10;
        }
    }
    lf_pop_style_props();
    }
}

static void renderbalance(){
    {
        lf_set_ptr_x_absolute(winw - 275);
        lf_set_ptr_y_absolute(winh - 625);
        LfUIElementProps props = lf_get_theme().text_props;
        props.border_width = 5.0f;
        props.border_color = (LfColor){255, 255, 255, 255};
        lf_push_style_props(props);
        lf_text("BALANCE:");
        lf_set_line_should_overflow(false);
        lf_pop_style_props();
    }
    {
        char balance_str[50];
        sprintf(balance_str, "%d", balance);

        lf_set_ptr_x_absolute(winw - 275);
        lf_set_ptr_y_absolute(winh - 600);
        LfUIElementProps props = lf_get_theme().text_props;
        props.border_width = 5.0f;
        props.border_color = (LfColor){255, 255, 255, 255};
        lf_push_style_props(props);
        lf_text(balance_str);
        lf_set_line_should_overflow(false);
        lf_pop_style_props();
    }
}

static void shuffle_digits(GLFWwindow* window) {
    for (int i = 0; i < 9; i++) {
        usleep(150000);
        number1random = (rand() % 9) + 1;
        number2random = (rand() % 9) + 1;
        number3random = (rand() % 9) + 1;

        number1 = number1random;
        number2 = number2random;
        number3 = number3random;

        glClear(GL_COLOR_BUFFER_BIT);

        lf_begin();

        renderbalance();
        spinningnumbers();

        lf_end();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main(){
    glfwInit();
    // UNCOMMENT FOR CLEANER LOOK BUT CANT MOVE AROUND !!!!!!!!!!!!!!!!!!!!!!!!!!
    glfwWindowHint( GLFW_DECORATED, GLFW_FALSE ); 
    //  UNCOMMENT FOR CLEANER LOOK BUT CANT MOVE AROUND !!!!!!!!!!!!!!!!!!!!!!!!!!
    GLFWwindow* window = glfwCreateWindow(winw, winh, "1", NULL, NULL);

    glfwMakeContextCurrent(window);

    lf_init_glfw(winw ,winh, window);

    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    titlefont = lf_load_font("./fonts/inter.ttf", 150);

    while(!glfwWindowShouldClose(window)){
        srand(time(0));
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f); 

        lf_begin();
        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}), ((vec2s){winw - WIN_MARGIN *2.0f, winh - WIN_MARGIN * 2.0f}),false);
        
        renderspinbuttons(window);
        renderbalance();
        spinningnumbers();

        lf_div_end();

        {
            lf_set_ptr_x_absolute(winw - 320);
            lf_set_ptr_y_absolute(winh - 150);
            LfUIElementProps props = lf_get_theme().text_props;
            props.border_width = 5.0f;
            props.border_color = (LfColor){255, 255, 255, 255};
            lf_push_style_props(props);
            lf_text("BET AMMOUNT:");
            lf_set_line_should_overflow(false);
            lf_pop_style_props();

            char bet_str[50];
            sprintf(bet_str, "%d", bet_size);

            lf_set_ptr_x_absolute(winw - 250);
            lf_set_ptr_y_absolute(winh - 125);
            props.border_width = 5.0f;
            props.border_color = (LfColor){255, 255, 255, 255};
            lf_push_style_props(props);
            lf_text(bet_str);
            lf_set_line_should_overflow(false);
            lf_pop_style_props();
        }

        lf_end();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    lf_free_font(&titlefont);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}