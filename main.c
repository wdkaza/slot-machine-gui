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
static int winw = 450;

static LfFont titlefont;

int balance = 1000;
int number1;
int number2;
int number3;
int bet_size = 10;

// Forward declaration of shuffle_digits
static void shuffle_digits();  // Add this declaration

static void checkwin(){
    if(number1 == number2 == number3){
        balance = balance + bet_size * 15;
    }
    if(number1 == number2 || number2 == number3){
        balance = balance + bet_size * 3;
    }
    else{
        balance = balance - bet_size;
    }
}

static void spinningnumbers(){
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

static void renderspinbuttons(){
    const float width = 160.0;
    lf_set_ptr_x_absolute(winw - width - WIN_MARGIN * 16.0f);
    lf_set_ptr_y_absolute(winh - 250);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;   
    props.margin_right = 0.0f;
    props.color = (LfColor){56, 224, 34,255};
    props.border_width = 0.0f;  
    props.corner_radius = 3.0f;
    lf_push_style_props(props);
    lf_set_line_should_overflow(false);
    if(lf_button_fixed("Spin!", width, -1) == LF_CLICKED){
        shuffle_digits();  // Initiate shuffle on button click
        checkwin();  // Check win after shuffle
    }
    lf_pop_style_props();
}

static void renderbalance(){
    lf_set_ptr_x_absolute(winw - 275);
    lf_set_ptr_y_absolute(winh - 625);
    LfUIElementProps props = lf_get_theme().text_props;
    props.border_width = 5.0f;
    props.border_color = (LfColor){255, 255, 255, 255};
    lf_push_style_props(props);
    lf_text("BALANCE:");
    lf_set_line_should_overflow(false);
    lf_pop_style_props();

    char balance_str[50];
    sprintf(balance_str, "%d", balance);
    lf_set_ptr_x_absolute(winw - 275);
    lf_set_ptr_y_absolute(winh - 600);
    lf_push_style_props(props);
    lf_text(balance_str);
    lf_set_line_should_overflow(false);
    lf_pop_style_props();
}

// Function to shuffle the numbers and update the screen during shuffle
static void shuffle_digits() {
    int number1random;
    for (int i = 0; i < 9; i++) {
        usleep(100000);  // Delay for shuffle effect
        number1random = (rand() % 9) + 1;
        printf("shuffling: %d\n", number1random);  // Debug output
        
        number1 = number1random;  // Update number1 with shuffled value

        // Redraw the screen to reflect the current shuffled number
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f); 
        
        lf_begin();
        
        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}), ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}), false);

        // Call the rendering functions
        renderbalance();
        spinningnumbers();

        lf_div_end();
        lf_end();

        // Swap buffers to display the current shuffled number
        glfwPollEvents();
        glfwSwapBuffers(glfwGetCurrentContext());
    }
}

int main() {
    glfwInit();
    glfwWindowHint( GLFW_DECORATED, GLFW_FALSE );  // Uncomment for a cleaner look but cannot move the window
    GLFWwindow* window = glfwCreateWindow(winw, winh, "1", NULL, NULL);
    glfwMakeContextCurrent(window);
    lf_init_glfw(winw ,winh, window);

    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    titlefont = lf_load_font("./fonts/inter.ttf", 150);

    while(!glfwWindowShouldClose(window)) {
        srand(time(0));
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f); 

        lf_begin();

        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}), ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}), false);
        
        renderspinbuttons();  // Display spin button
        renderbalance();      // Display balance
        spinningnumbers();    // Display numbers

        lf_div_end();
        lf_end();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    lf_free_font(&titlefont);
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
