//
//  main.cpp
//  gll
//
//  Created by lijingwei on 2021/12/3.
//

#include <iostream>
#include <../includes/GLEW/glew.h>
#include <../includes/GLFW/glfw3.h>

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {
        
    };
}

static void GLCheckError()
{
    while (GLenum err = glGetError()) {
        std::cout << "[GLError]: " << err << std::endl;
    }
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    // id glCreateShader的句柄 Specifies the handle of the shader object whose source code is to be replaced.
    // count 这边传入的src是一个 char** 类型的数组指针，我们在这边需要指定这个数组内有多少个char*指针 这边只有一个 所以传入1 Specifies the number of elements in the string and length arrays.
    // char**指针的地址 Specifies an array of pointers to strings containing the source code to be loaded into the shader.
    // length 这边char**指针内的char*数量大于1的话可以在这版传入一个数组，这个数组包含每个char*的长度 Specifies an array of string lengths.
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        //some thing wrong
        int lenth;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenth);
        char* message = (char*)alloca(lenth * sizeof(char));
        glGetShaderInfoLog(id, lenth, &lenth, message);
        std::cout << "Shader Compile" << (type == GL_FRAGMENT_SHADER ? "Fragment" : "Vertex") << "Failed" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (!glfwInit())
        return 0;
    
//    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
//    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif
    GLFWwindow* window = glfwCreateWindow(640, 480, "Wave Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }
    
    glfwMakeContextCurrent(window);
    
    //这个操作必须在makeContextCurrent 之后
    if (glewInit() != GLEW_OK)
        return 0;
    
    std::cout << "GL_Version : " << glGetString(GL_VERSION) << std::endl;
    
    float positions[] = {
        -0.5, -0.5, //0
         0.5, -0.5, //1
         0.5,  0.5,
        -0.5,  0.5
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 0, 3
    };
    

    //glGenBuffers(1, &buffer); //number of buffers, return an id of buffer which written in the povide uint pointer
    //设置vertex array object
    //这个东西好像没有指定任何与之关联的数组或vertex 但是又不能不写 就离谱
    //难道这个是管理下面VBO和EBO的前提?
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    //设置vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(float), positions, GL_STATIC_DRAW);
    
    //https://www.youtube.com/watch?v=0p9VxImr7Y0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=4 18:00 glBindBuffer
    

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //size 每组vertex长度 这边位置信息始2个float组成一个vertex 所以是2
    //type 单个数据的类型
    //normal 是否需要让数据归一化 bool
    //stride 每组vertex数据的步长 bit为单位 这边为2个float的长度 8
    //pointer pos/tex_cord/color 指代起始位置
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);



    
    std::string vs = "#version 330 core\n"
                     "\n"
                     "layout(location = 0) in vec4 position;\n"
                     "void main()\n"
                     "{\n"
                     "  gl_Position = position;\n"
                     "}\n";
    
    std::string fs = "#version 330 core\n"
                     "\n"
                     "layout(location = 0) out vec4 color;\n"
                     "void main()\n"
                     "{\n"
                     "  color = vec4(1.0, 0.3, 0.5, 1.0);\n"
                     "}\n";

    unsigned int program = CreateShaderProgram(vs, fs);
    glUseProgram(program);
    
    
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        GLClearError();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        GLCheckError();
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VBO);
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}
