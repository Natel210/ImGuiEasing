#include "ImGuiEasingCore.h"
#include <string>
#include <algorithm>

#include <Library/SDL2/include/SDL.h>
#include <Library/SDL2/include/SDL_opengl.h>
//#include <Library/SDL2/include/SDL_syswm.h>

#include <Library/imgui/imgui.h>
#include <Library/imgui/backends/imgui_impl_sdl2.h>
#include <Library/imgui/backends/imgui_impl_opengl2.h>

namespace ImGuiEasing
{
    static SDL_Window* mainWindow = nullptr;
    static SDL_GLContext glContext;
    static ImGuiContext* imGuiContext = nullptr;
    static ImFont* coreFont = nullptr;

    std::shared_ptr<ViewBase> ImGuiEasingCore::_rootView = nullptr;

    ImguiEasingError ImGuiEasingCore::Init()
    {
        // Setup SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            SDL_Quit();
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_Init_Fail, SDL_GetError() };
        }

        // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

        // Setup window
        if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0)
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_GL_SetAttribute_Fail, SDL_GetError() };
        if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) != 0)
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_GL_SetAttribute_Fail, SDL_GetError() };
        if (SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) != 0)
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_GL_SetAttribute_Fail, SDL_GetError() };
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2) != 0)
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_GL_SetAttribute_Fail, SDL_GetError() };
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) != 0)
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_GL_SetAttribute_Fail, SDL_GetError() };

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS
            /*| SDL_WINDOW_ALWAYS_ON_TOP*/ | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        mainWindow = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, window_flags);
        if (mainWindow == nullptr)
        {
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_CreateWindow_Fail, SDL_GetError() };
        }
        SDL_SetWindowOpacity(mainWindow, 1.0f);

        glContext = SDL_GL_CreateContext(mainWindow);
        if (glContext == nullptr)
        {
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_GL_CreateContext_Fail, SDL_GetError() };
        }
        if (SDL_GL_MakeCurrent(mainWindow, glContext) != 0)
        {
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return ImguiEasingError{ ImguiEasingErrorCode::SDL_GL_CreateContext_Fail, SDL_GetError() };
        }
        SDL_GL_SetSwapInterval(1); // Enable vsync
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        //ImGui::CreateContext();
        imGuiContext = ImGui::CreateContext();
        if (imGuiContext == nullptr)
        {
            ImGui::DestroyContext(imGuiContext);
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return ImguiEasingError{ ImguiEasingErrorCode::Imgui_CreateContext_Fail, SDL_GetError() };
        }

        ImGui::SetCurrentContext(imGuiContext);
        ImGuiIO& imGuiIO = ImGui::GetIO();
        (void)imGuiIO;
        imGuiIO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        imGuiIO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        imGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        imGuiIO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //imGuiIO.ConfigViewportsNoAutoMerge = true;
        imGuiIO.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (imGuiIO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        if (ImGui_ImplSDL2_InitForOpenGL(mainWindow, glContext) == false)
        {
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext(imGuiContext);
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return ImguiEasingError{ ImguiEasingErrorCode::ImGui_ImplSDL2_InitForOpenGL_Fail, "ImGui_ImplSDL2_InitForOpenGL_Fail"};
        }
        if (ImGui_ImplOpenGL2_Init() == false)
        {
            ImGui_ImplOpenGL2_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext(imGuiContext);
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return ImguiEasingError{ ImguiEasingErrorCode::ImGui_ImplOpenGL2_Init_Fail,  "ImGui_ImplOpenGL2_Init_Fail"};
        }
        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //imGuiIO.Fonts->AddFontDefault();
        //imGuiIO.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //imGuiIO.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //imGuiIO.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //imGuiIO.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = imGuiIO.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, imGuiIO.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != nullptr);

        //const ImWchar ranges[] = {
        //    0x0020, 0x00FF, // Basic Latin + Latin Supplement
        //    0x2000, 0x206F, // General Punctuation
        //    0x2200, 0x22FF, // Mathematical Operators
        //    0x3131, 0x3163, // Korean alphabets
        //    0xAC00, 0xD7A3, // Korean characters
        //    0xFFFD, 0xFFFD, // Invalid
        //    0,
        //};
        coreFont = imGuiIO.Fonts->AddFontFromFileTTF(
            "C:\\Users\\UBISAM\\AppData\\Local\\Microsoft\\Windows\\Fonts\\D2Coding.ttf",
            18.0f, NULL, imGuiIO.Fonts->);
        imGuiIO.FontDefault = coreFont;
        // Our state

        return ImguiEasingError{ ImguiEasingErrorCode::Ok, "" };
    }

    ImguiEasingError ImGuiEasingCore::Execution()
    {
        // Main loop
        bool done = false;
        while (!done)
        {
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    done = true;
                if (event.type == SDL_WINDOWEVENT 
                    && event.window.event == SDL_WINDOWEVENT_CLOSE 
                    && event.window.windowID == SDL_GetWindowID(mainWindow))
                    done = true;
            }
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            // Root View Render
            if (_rootView != nullptr)
            {
                _rootView->Render();
            }

            // Imgui Rendering
            ImGui::Render();

            ImGuiIO imGuiIO = ImGui::GetIO();
            ImVec2 displaySize = imGuiIO.DisplaySize;
            glViewport(0, 0, static_cast<int>(displaySize.x), static_cast<int>(displaySize.y));

            glClear(GL_COLOR_BUFFER_BIT);
            //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

            // Update and Render additional Platform Windows
            // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
            //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
            if (imGuiIO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
                SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
            }

            SDL_GL_SwapWindow(mainWindow);
        }

        // Cleanup
        _rootView.reset();

        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext(imGuiContext);

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return ImguiEasingError{ ImguiEasingErrorCode::Ok, "" };
    }

    void ImGuiEasingCore::ChangeView(std::shared_ptr<ViewBase> rootView)
    {
        if (rootView == nullptr)
            return;
        _rootView.reset();
        _rootView = rootView;
    }

    std::shared_ptr<ViewBase> ImGuiEasingCore::GetRootView_ToViewBase()
    {
        return _rootView;
    }

    void ImGuiEasingCore::WindowMaximize()
    {
        SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    void ImGuiEasingCore::WindowMinimize()
    {
        SDL_MinimizeWindow(mainWindow);
    }

    void ImGuiEasingCore::WindowRestored()
    {
        SDL_SetWindowFullscreen(mainWindow, 0);
    }

    void ImGuiEasingCore::WindowGetPos(int& x, int& y)
    {
        SDL_GetWindowPosition(mainWindow, &x, &y);
    }

    void ImGuiEasingCore::WindowSetPos(int x, int y)
    {
        SDL_SetWindowPosition(mainWindow,x,y);
    }

    void ImGuiEasingCore::WindowClose()
    {
        SDL_Event closeEvent;
        SDL_zero(closeEvent); // 이벤트 구조체를 0으로 초기화합니다.
        closeEvent.type = SDL_WINDOWEVENT; // 이벤트 타입을 SDL_WINDOWEVENT로 설정합니다.
        closeEvent.window.event = SDL_WINDOWEVENT_CLOSE; // window 이벤트 타입을 SDL_WINDOWEVENT_CLOSE로 설정합니다.
        closeEvent.window.windowID = SDL_GetWindowID(mainWindow); // 이벤트를 발송할 윈도우의 ID를 설정합니다.
        SDL_PushEvent(&closeEvent); // 생성한 이벤트를 SDL 이벤트 큐에 추가합니다.
    }

    void ImGuiEasingCore::ImGuiStyleColorDark()
    {
        ImGui::StyleColorsDark();
    }

    void ImGuiEasingCore::ImGuiStyleColorClassic()
    {
        ImGui::StyleColorsClassic();
    }

    void ImGuiEasingCore::ImGuiStyleColorLight()
    {
        ImGui::StyleColorsLight();
    }

    ImGuiEasingCore::ImGuiEasingCore()
    {
    }

    ImGuiEasingCore::~ImGuiEasingCore()
    {
        _rootView.reset();
    }

}