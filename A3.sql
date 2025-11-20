-- A3.sql
-- Borrower_final & Fine_final Management

-- Prompt for borrower details
\prompt 'Enter Rollin: ' rollin
\prompt 'Enter Name: ' name
\prompt 'Enter Date of Issue (YYYY-MM-DD): ' dateofissue
\prompt 'Enter Name of Book: ' nameofbook
\prompt 'Enter Status (I for Issued, R for Returned): ' status

-- Insert borrower record
INSERT INTO Borrower_final(Rollin, Name, DateOfIssue, NameOfBook, Status)
VALUES ( :'rollin', :'name', :'dateofissue', :'nameofbook', :'status' );

-- Fine calculation + update block
DO $$
DECLARE
    v_rollin INT;
    v_dateofissue DATE;
    v_days INT;
    v_fine INT := 0;
BEGIN
    -- Get the latest Rollin inserted
    SELECT Rollin INTO v_rollin
    FROM Borrower_final
    ORDER BY Rollin DESC
    LIMIT 1;

    -- Get the date of issue for that Rollin
    SELECT DateOfIssue INTO v_dateofissue
    FROM Borrower_final
    WHERE Rollin = v_rollin;

    -- Calculate number of days elapsed
    v_days := CURRENT_DATE - v_dateofissue;

    -- Apply fine rules
    IF v_days BETWEEN 15 AND 30 THEN
        v_fine := (v_days - 14) * 5;  -- Fine of Rs. 5 per day after 14 days
    ELSIF v_days > 30 THEN
        v_fine := (v_days - 14) * 50; -- Fine of Rs. 50 per day after 14 days
    END IF;

    -- Update Borrower status if still issued
    UPDATE Borrower_final
    SET Status = 'R'
    WHERE Rollin = v_rollin AND Status = 'I';

    -- Insert fine record if fine exists
    IF v_fine > 0 THEN
        INSERT INTO Fine_final(Roll_no, Date, Amt)
        VALUES (v_rollin, CURRENT_DATE, v_fine);
    END IF;

    -- Display processed message
    RAISE NOTICE 'Book processed. Days = %, Fine = Rs. %', v_days, v_fine;
END $$;






