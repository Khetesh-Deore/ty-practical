create table books(
    accno int,
    title varchar,
    author varchar,
    publisher varchar,
    countof int
);

create table lib_audit(
    accno int,
    title varchar,
    author varchar,
    publisher varchar,
    countof int,
    dateof timestamp,
    status char
);

create or replace function t_function()
returns trigger as $$
begin  
    if ( tg_op='UPDATE') then
        insert into lib_audit values(old.accno,old.title,old.author,old.publisher,old.countof,now(),'u');
        return new;
    elsif (tg_op='DELETE') then
        insert into lib_audit values(old.accno,old.title,old.author,old.publisher,old.countof,now(),'d');
        return old;
    end if;
    return null;
end;
$$ language plpgsql;

create trigger t_trigger
before delete or update on books
for each row
execute function t_function();

insert into books values(123,'sd','asdfg','wsedrf',213);

update books set author='akshada' where accno=123;

delete from books where accno=123;
