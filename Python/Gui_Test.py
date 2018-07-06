import tkinter
from tkinter import font
from tkinter import ttk

class MyFrame:
    __root = tkinter.Tk()

    # Aplication 크기
    __maxWidth = 640
    __maxHeight = 400
    
    # 디스플레이 정보
    __screenWidth = __root.winfo_screenwidth()
    __screenHeight = __root.winfo_screenheight()

    # 프로그램 시작 위치
    left = (__screenWidth / 2) - (__maxWidth / 2) 
    top = (__screenHeight / 2) - (__maxHeight / 2)

    # Aplication 타이틀과 위치 및 크기 설정
    __root.title("Test for Python Tkinter")
    __root.geometry("%dx%d+%d+%d" % (__maxWidth, __maxHeight, left, top ) )
    __root.resizable(False, False)

    def __init__(self):
        self.mainFrame = tkinter.Frame(self.__root)
        self.mainFrame.pack()


        self.progressbar = tkinter.ttk.Progressbar(self.mainFrame, orient = "horizontal", maximum = 100)
        self.progressbar.pack(fill = "both")

        self.progressbar.start(30)

    def run(self):

        # Run main application
        self.__root.mainloop()

# Run main function
if __name__ == "__main__":
    root = MyFrame()
    root.run()