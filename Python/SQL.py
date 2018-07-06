import pymysql.cursors

conn = pymysql.connect(host = "localhost", user = "user", password = None, db = "pysql", charset = "utf8mb4")

try:
    with conn.cursor() as cursor:

        sql = """INSERT INTO user_info( 
            USER_ID, USER_PASSWD, USER_NAME, 
            USER_BIRTHDAY, USER_GENDER, USER_EMAIL, 
            USER_PHONE, USER_CREATEDAY) 
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s)"""

        cursor.execute(sql,
            ("wjsdbsgus", "4dminroot!", "전윤현",
            "1998-03-28", "Male", "wjsdbsgus245@naver.com",
            "010-1234-5555", "2018-07-04 11:13:42") )

    conn.commit()
    print(cursor.lastrowid)
finally:
    conn.close()
