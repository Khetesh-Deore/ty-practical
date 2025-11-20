
CREATE TABLE IF NOT EXISTS borrower(
     rollin INT,
	 name VARCHAR(100),
	 dateofissue DATE,
	 nameofbook VARCHAR(100),
	 stat CHAR
);

CREATE TABLE IF NOT EXISTS fine(
	roll_no INT,
	 dateof DATE,
	 amt INT
);

\prompt 'ENTER Roll NO:' rollin
\prompt 'Name:' name
\prompt 'DATE OF ISSUE:' dateofissue
\prompt ' Book Name:' nameofbook
\prompt 'Status:(I or R):' stat

INSERT INTO borrower VALUES(:'rollin', :'name', :'dateofissue', :'nameofbook', :'stat');
DO $$
DECLARE 
  v_roll INT;
  v_date DATE;
  v_fine INT :=0;
  v_day INT;
BEGIN 
  SELECT rollin INTO v_roll
  FROM borrower
  ORDER BY rollin DESC
  LIMIT(1);

  SELECT dateofissue INTO v_date
  FROM borrower
  WHERE rollin=v_roll;

   v_day:=CURRENT_DATE -v_date;

   IF v_day BETWEEN 15 AND 30 then
     v_fine:=(v_day-14)*5;
   ELSIF v_day>30 then
    v_fine:=(v_day-14)*50;
	END IF;

  UPDATE borrower
  SET stat='R'
  WHERE rollin=v_roll AND stat='I';

  IF v_fine>0 then
    INSERT INTO fine(roll_no,dateof,amt) VALUES(v_roll,CURRENT_DATE,v_fine);
  END IF;
END $$;




